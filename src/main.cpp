#include <iostream>
#include <memory>

#include "camera.hpp"

using namespace std;

void showState(const capture::Camera& camera) {
  cout << "Ready: " << boolalpha << camera.isReady() << endl;
  cout << "Capture: " << boolalpha << camera.isCapture() << endl;
  cout << "Pause: " << boolalpha << camera.isPause() << endl;
  cout << endl;
}

int main(void) {
  cout << "[Initial state]" << endl;
  unique_ptr<capture::Camera> camera = make_unique<capture::Camera>();
  showState(*camera);

  cout << "[Open]" << endl;
  camera->open();
  showState(*camera);

  if (!camera->isReady()) {
    cout << "[ERROR] Camera is not ready." << endl;
    return -1;
  }

  cout << "[Start]" << endl;
  camera->start();
  showState(*camera);

  if (!camera->isCapture()) {
    cout << "[ERROR] Capture failed." << endl;
    return -1;
  }

  cout << "[Pause]" << endl;
  camera->pause();
  showState(*camera);

  cout << "[Resume]" << endl;
  camera->resume();
  showState(*camera);

  cout << "[Stop]" << endl;
  camera->stop();
  showState(*camera);

  cout << "[Close]" << endl;
  camera->close();
  showState(*camera);

  camera.reset();

  return 0;
}
