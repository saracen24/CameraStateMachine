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

CameraStateMachine::State::State(CameraStateMachine *context)
    : m_csm(context) {}

CameraStateMachine::Off::Off(CameraStateMachine *csm) : State(csm) {}

void CameraStateMachine::Off::open() {
  if (m_csm->onOpen()) m_csm->change(StateType::READY);
}

CameraStateMachine::Ready::Ready(CameraStateMachine *csm) : State(csm) {}

void CameraStateMachine::Ready::start() {
  if (m_csm->onStart()) m_csm->change(StateType::CAPTURE);
}

void CameraStateMachine::Ready::close() {
  if (m_csm->onClose()) m_csm->change(StateType::OFF);
}

CameraStateMachine::Capture::Capture(CameraStateMachine *csm) : State(csm) {}

void CameraStateMachine::Capture::pause() {
  if (m_csm->onPause()) m_csm->change(StateType::PAUSE);
}

void CameraStateMachine::Capture::stop() {
  if (m_csm->onStop()) m_csm->change(StateType::READY);
}

CameraStateMachine::Pause::Pause(CameraStateMachine *csm) : State(csm) {}

void CameraStateMachine::Pause::resume() {
  if (m_csm->onResume()) m_csm->change(StateType::CAPTURE);
}

void CameraStateMachine::Pause::stop() {
  if (m_csm->onStop()) m_csm->change(StateType::READY);
}

}  // namespace capture
