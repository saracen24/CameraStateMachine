#pragma once

#include "camera_state_machine.hpp"

namespace aiz {

class Camera final : public CameraStateMachine {
 public:
  explicit Camera() = default;
  ~Camera() override = default;

  //! NonCopyable.
  Camera(const Camera&) = delete;
  Camera& operator=(const Camera&) = delete;
  //! NonMovable.
  Camera(Camera&&) = delete;
  Camera& operator=(Camera&&) = delete;

 private:
  bool onOpen() override;
  bool onStart() override;
  bool onPause() override;
  bool onResume() override;
  bool onStop() override;
  bool onClose() override;
};

}  // namespace aiz
