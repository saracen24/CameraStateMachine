#include "camera_state_machine.hpp"

namespace capture {

CameraStateMachine::CameraStateMachine() : m_state(new Off()) {}

CameraStateMachine::~CameraStateMachine() {
  if (m_state) delete m_state;
}

void CameraStateMachine::open() {
  if (!m_state->open(this)) return;
  m_isReady = true;
}

void CameraStateMachine::start() {
  if (!m_state->start(this)) return;
  m_isCapture = true;
}

void CameraStateMachine::pause() {
  if (!m_state->pause(this)) return;
  m_isPause = true;
}

void CameraStateMachine::resume() {
  if (!m_state->resume(this)) return;
  m_isPause = false;
}

void CameraStateMachine::stop() {
  if (!m_state->stop(this)) return;
  m_isCapture = false;
}

void CameraStateMachine::close() {
  if (!m_state->close(this)) return;
  m_isReady = false;
}

bool CameraStateMachine::isReady() const noexcept { return m_isReady; }

bool CameraStateMachine::isCapture() const noexcept { return m_isCapture; }

bool CameraStateMachine::isPause() const noexcept { return m_isPause; }

void CameraStateMachine::change(CameraStateMachine::State* const state) {
  if (m_state) delete m_state;
  m_state = state;
}

bool CameraStateMachine::State::open(CameraStateMachine* const) {
  return false;
}

bool CameraStateMachine::State::start(CameraStateMachine* const) {
  return false;
}

bool CameraStateMachine::State::pause(CameraStateMachine* const) {
  return false;
}

bool CameraStateMachine::State::resume(CameraStateMachine* const) {
  return false;
}

bool CameraStateMachine::State::stop(CameraStateMachine* const) {
  return false;
}

bool CameraStateMachine::State::close(CameraStateMachine* const) {
  return false;
}

bool CameraStateMachine::Off::open(CameraStateMachine* const csm) {
  if (!csm->onOpen()) return false;
  csm->change(new Ready());
  return true;
}

bool CameraStateMachine::Ready::start(CameraStateMachine* const csm) {
  if (!csm->onStart()) return false;
  csm->change(new Capture());
  return true;
}

bool CameraStateMachine::Ready::close(CameraStateMachine* const csm) {
  if (!csm->onClose()) return false;
  csm->change(new Off());
  return true;
}

bool CameraStateMachine::Capture::pause(CameraStateMachine* const csm) {
  if (!csm->onPause()) return false;
  csm->change(new Pause());
  return true;
}

bool CameraStateMachine::Capture::stop(CameraStateMachine* const csm) {
  if (!csm->onStop()) return false;
  csm->change(new Ready());
  return true;
}

bool CameraStateMachine::Pause::resume(CameraStateMachine* const csm) {
  if (!csm->onResume()) return false;
  csm->change(new Capture());
  return true;
}

bool CameraStateMachine::Pause::stop(CameraStateMachine* const csm) {
  if (!csm->onStop()) return false;
  csm->change(new Ready());
  return true;
}

}  // namespace capture
