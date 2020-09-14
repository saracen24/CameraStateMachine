#include "camera.hpp"

#include <iostream>

using namespace std;

namespace aiz {

bool Camera::onOpen() {
  cout << ">> Do on open ..." << endl;
  return true;
}

bool Camera::onStart() {
  cout << ">> Do on start ..." << endl;
  return true;
}

bool Camera::onPause() {
  cout << ">> Do on pause ..." << endl;
  return true;
}

bool Camera::onResume() {
  cout << ">> Do on resume ..." << endl;
  return true;
}

bool Camera::onStop() {
  cout << ">> Do on stop ..." << endl;
  return true;
}

bool Camera::onClose() {
  cout << ">> Do on close ..." << endl;
  return true;
}

}  // namespace aiz
