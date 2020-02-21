#include <iostream>
#include <memory>

#include "camera.hpp"

using namespace std;
using namespace aiz::capture;

static const array<const char*, 4> kState{"OFF", "READY", "CAPTURE", "PAUSE"};

void showState(const Camera::State state) {
  cout << "State: " << boolalpha << kState.at(static_cast<size_t>(state)) << endl
       << endl;
}

int main() {
  cout << "[Initial state]" << endl;
  unique_ptr<Camera> camera = make_unique<Camera>();
  showState(camera->state());

  cout << "[Open]" << endl;
  camera->open();
  showState(camera->state());

  if (camera->state() != Camera::State::READY) {
    cout << "[ERROR] Camera is not ready." << endl;
    return -1;
  }

  cout << "[Start]" << endl;
  camera->start();
  showState(camera->state());

  if (camera->state() != Camera::State::CAPTURE) {
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
