#include <iostream>
#include <memory>

#include "camera.hpp"

using namespace std;
using namespace capture;

static const char* STATE[]{"OFF", "READY", "CAPTURE", "PAUSE"};

void showState(const Camera::StateType state) {
  cout << "State: " << boolalpha << STATE[static_cast<size_t>(state)] << endl;
  cout << endl;
}

int main() {
  cout << "[Initial state]" << endl;
  unique_ptr<Camera> camera = make_unique<Camera>();
  showState(camera->state());

  cout << "[Open]" << endl;
  camera->open();
  showState(camera->state());

  if (camera->state() != Camera::StateType::READY) {
    cout << "[ERROR] Camera is not ready." << endl;
    return -1;
  }

  cout << "[Start]" << endl;
  camera->start();
  showState(camera->state());

  if (camera->state() != Camera::StateType::CAPTURE) {
    cout << "[ERROR] Capture failed." << endl;
    return -1;
  }

  cout << "[Pause]" << endl;
  camera->pause();
  showState(camera->state());

  cout << "[Resume]" << endl;
  camera->resume();
  showState(camera->state());

  cout << "[Stop]" << endl;
  camera->stop();
  showState(camera->state());

  cout << "[Close]" << endl;
  camera->close();
  showState(camera->state());

  camera.reset();

  return 0;
}
