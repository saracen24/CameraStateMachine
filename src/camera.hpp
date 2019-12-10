#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "camera_state_machine.hpp"

namespace capture {

class Camera : public CameraStateMachine {
 public:
  explicit Camera() = default;
  ~Camera() final;

 private:
  bool onOpen() final;
  bool onStart() final;
  bool onPause() final;
  bool onResume() final;
  bool onStop() final;
  bool onClose() final;
};

}  // namespace capture

#endif
