#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "camera_state_machine.hpp"

namespace capture {

class Camera : public CameraStateMachine {
 public:
  explicit Camera() = default;
  ~Camera() final;

  //! NonCopyable.
  Camera(const Camera&) = delete;
  Camera(Camera&&) = delete;
  Camera& operator=(const Camera&) = delete;
  Camera& operator=(Camera&&) = delete;

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
