#include "camera_state_machine.hpp"

namespace capture {

CameraStateMachine::CameraStateMachine()
    : m_s{new Off(this), new Ready(this), new Capture(this), new Pause(this)} {}

CameraStateMachine::~CameraStateMachine() {
  for (const BaseState *state : m_s) delete state;
}

void CameraStateMachine::open() {
  m_s.at(static_cast<size_t>(m_state))->open();
}

void CameraStateMachine::start() {
  m_s.at(static_cast<size_t>(m_state))->start();
}

void CameraStateMachine::pause() {
  m_s.at(static_cast<size_t>(m_state))->pause();
}

void CameraStateMachine::resume() {
  m_s.at(static_cast<size_t>(m_state))->resume();
}

void CameraStateMachine::stop() {
  m_s.at(static_cast<size_t>(m_state))->stop();
}

void CameraStateMachine::close() {
  m_s.at(static_cast<size_t>(m_state))->close();
}

CameraStateMachine::State CameraStateMachine::state() const noexcept {
  return m_state;
}

void CameraStateMachine::change(State state) { m_state = state; }

void CameraStateMachine::BaseState::open() {}

void CameraStateMachine::BaseState::start() {}

void CameraStateMachine::BaseState::pause() {}

void CameraStateMachine::BaseState::resume() {}

void CameraStateMachine::BaseState::stop() {}

void CameraStateMachine::BaseState::close() {}

CameraStateMachine *CameraStateMachine::BaseState::context() const noexcept {
  return m_csm;
}

CameraStateMachine::BaseState::BaseState(CameraStateMachine *csm)
    : m_csm(csm) {}

CameraStateMachine::Off::Off(CameraStateMachine *csm) : BaseState(csm) {}

void CameraStateMachine::Off::open() {
  CameraStateMachine *csm = context();
  if (csm->onOpen()) csm->change(State::READY);
}

CameraStateMachine::Ready::Ready(CameraStateMachine *csm) : BaseState(csm) {}

void CameraStateMachine::Ready::start() {
  CameraStateMachine *csm = context();
  if (csm->onStart()) csm->change(State::CAPTURE);
}

void CameraStateMachine::Ready::close() {
  CameraStateMachine *csm = context();
  if (csm->onClose()) csm->change(State::OFF);
}

CameraStateMachine::Capture::Capture(CameraStateMachine *csm)
    : BaseState(csm) {}

void CameraStateMachine::Capture::pause() {
  CameraStateMachine *csm = context();
  if (csm->onPause()) csm->change(State::PAUSE);
}

void CameraStateMachine::Capture::stop() {
  CameraStateMachine *csm = context();
  if (csm->onStop()) csm->change(State::READY);
}

CameraStateMachine::Pause::Pause(CameraStateMachine *csm) : BaseState(csm) {}

void CameraStateMachine::Pause::resume() {
  CameraStateMachine *csm = context();
  if (csm->onResume()) csm->change(State::CAPTURE);
}

void CameraStateMachine::Pause::stop() {
  CameraStateMachine *csm = context();
  if (csm->onStop()) csm->change(State::READY);
}

}  // namespace capture
