#include "camera_state_machine.hpp"

using namespace std;

namespace aiz {

CameraStateMachine::~CameraStateMachine() {
  for (const BaseState* state : kInstance) delete state;
}

void CameraStateMachine::open() { kInstance.at(mState)->open(); }

void CameraStateMachine::start() { kInstance.at(mState)->start(); }

void CameraStateMachine::pause() { kInstance.at(mState)->pause(); }

void CameraStateMachine::resume() { kInstance.at(mState)->resume(); }

void CameraStateMachine::stop() { kInstance.at(mState)->stop(); }

void CameraStateMachine::close() { kInstance.at(mState)->close(); }

CameraStateMachine::State CameraStateMachine::state() const noexcept {
  return mState;
}

void CameraStateMachine::change(State state) { mState = state; }

void CameraStateMachine::BaseState::open() {}

void CameraStateMachine::BaseState::start() {}

void CameraStateMachine::BaseState::pause() {}

void CameraStateMachine::BaseState::resume() {}

void CameraStateMachine::BaseState::stop() {}

void CameraStateMachine::BaseState::close() {}

CameraStateMachine* CameraStateMachine::BaseState::context() const noexcept {
  return mCsm;
}

CameraStateMachine::BaseState::BaseState(CameraStateMachine* csm) : mCsm(csm) {}

CameraStateMachine::Off::Off(CameraStateMachine* csm) : BaseState(csm) {}

void CameraStateMachine::Off::open() {
  CameraStateMachine* csm = context();
  if (csm->onOpen()) csm->change(State::READY);
}

CameraStateMachine::Ready::Ready(CameraStateMachine* csm) : BaseState(csm) {}

void CameraStateMachine::Ready::start() {
  CameraStateMachine* csm = context();
  if (csm->onStart()) csm->change(State::CAPTURE);
}

void CameraStateMachine::Ready::close() {
  CameraStateMachine* csm = context();
  if (csm->onClose()) csm->change(State::OFF);
}

CameraStateMachine::Capture::Capture(CameraStateMachine* csm)
    : BaseState(csm) {}

void CameraStateMachine::Capture::pause() {
  CameraStateMachine* csm = context();
  if (csm->onPause()) csm->change(State::PAUSE);
}

void CameraStateMachine::Capture::stop() {
  CameraStateMachine* csm = context();
  if (csm->onStop()) csm->change(State::READY);
}

CameraStateMachine::Pause::Pause(CameraStateMachine* csm) : BaseState(csm) {}

void CameraStateMachine::Pause::resume() {
  CameraStateMachine* csm = context();
  if (csm->onResume()) csm->change(State::CAPTURE);
}

void CameraStateMachine::Pause::stop() {
  CameraStateMachine* csm = context();
  if (csm->onStop()) csm->change(State::READY);
}

}  // namespace aiz
