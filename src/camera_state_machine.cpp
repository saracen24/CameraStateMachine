#include "camera_state_machine.hpp"

namespace capture {

CameraStateMachine::CameraStateMachine()
    : m_s{new Off(this), new Ready(this), new Capture(this), new Pause(this)} {}

CameraStateMachine::~CameraStateMachine() {
  for (const State *state : m_s) delete state;
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

CameraStateMachine::StateType CameraStateMachine::state() const noexcept {
  return m_state;
}

void CameraStateMachine::change(CameraStateMachine::StateType state) {
  m_state = state;
}

void CameraStateMachine::State::open() {}

void CameraStateMachine::State::start() {}

void CameraStateMachine::State::pause() {}

void CameraStateMachine::State::resume() {}

void CameraStateMachine::State::stop() {}

void CameraStateMachine::State::close() {}

CameraStateMachine *CameraStateMachine::State::context() const noexcept {
  return m_csm;
}

CameraStateMachine::State::State(CameraStateMachine *csm) : m_csm(csm) {}

CameraStateMachine::Off::Off(CameraStateMachine *csm) : State(csm) {}

void CameraStateMachine::Off::open() {
  CameraStateMachine *csm = context();
  if (csm->onOpen()) csm->change(StateType::READY);
}

CameraStateMachine::Ready::Ready(CameraStateMachine *csm) : State(csm) {}

void CameraStateMachine::Ready::start() {
  CameraStateMachine *csm = context();
  if (csm->onStart()) csm->change(StateType::CAPTURE);
}

void CameraStateMachine::Ready::close() {
  CameraStateMachine *csm = context();
  if (csm->onClose()) csm->change(StateType::OFF);
}

CameraStateMachine::Capture::Capture(CameraStateMachine *csm) : State(csm) {}

void CameraStateMachine::Capture::pause() {
  CameraStateMachine *csm = context();
  if (csm->onPause()) csm->change(StateType::PAUSE);
}

void CameraStateMachine::Capture::stop() {
  CameraStateMachine *csm = context();
  if (csm->onStop()) csm->change(StateType::READY);
}

CameraStateMachine::Pause::Pause(CameraStateMachine *csm) : State(csm) {}

void CameraStateMachine::Pause::resume() {
  CameraStateMachine *csm = context();
  if (csm->onResume()) csm->change(StateType::CAPTURE);
}

void CameraStateMachine::Pause::stop() {
  CameraStateMachine *csm = context();
  if (csm->onStop()) csm->change(StateType::READY);
}

}  // namespace capture
