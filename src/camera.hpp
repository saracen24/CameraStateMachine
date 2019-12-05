#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "camera_state_machine.hpp"

namespace capture {

class Camera : public CameraStateMachine {
 public:
  explicit Camera() = default;
  virtual ~Camera() override final;

 private:
  virtual bool onOpen() override final;
  virtual bool onStart() override final;
  virtual bool onPause() override final;
  virtual bool onResume() override final;
  virtual bool onStop() override final;
  virtual bool onClose() override final;
};

}  // namespace capture

#endif
