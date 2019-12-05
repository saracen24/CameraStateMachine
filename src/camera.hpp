#pragma once

#include <iostream>

#include "camera_state_machine.hpp"

namespace capture {

class Camera : public CameraStateMachine {
 public:
  explicit Camera() = default;
  virtual ~Camera() override final = default;

 private:
  virtual bool onOpen() override final {
    std::cout << ">> Do on open ..." << std::endl;
    return true;
  }

  virtual bool onStart() override final {
    std::cout << ">> Do on start ..." << std::endl;
    return true;
  }

  virtual bool onPause() override final {
    std::cout << ">> Do on pause ..." << std::endl;
    return true;
  }

  virtual bool onResume() override final {
    std::cout << ">> Do on resume ..." << std::endl;
    return true;
  }

  virtual bool onStop() override final {
    std::cout << ">> Do on stop ..." << std::endl;
    return true;
  }

  virtual bool onClose() override final {
    std::cout << ">> Do on close ..." << std::endl;
    return true;
  }
};

}  // namespace capture
