//
// Created by Mateusz Palkowski on 26/10/2022.
//

#include "dynamic_buffer_scene.h"

#include <iostream>

#include "GLFW/glfw3.h"

void DynamicBufferScene::OnUpdate(float deltaTime) {
  if (size_changed_) {
    // recalculate projection matrix
    std::cout << "Size changed" << std::endl;
    size_changed_ = false;
  }

  if (mouse_moved_) {
    std::cout << "Mouse moved" << std::endl;
    mouse_moved_ = false;
  }

  if (up_) {
    std::cout << "up" << std::endl;
  }
  if (down_) {
    std::cout << "down" << std::endl;
  }
  if (left_) {
    std::cout << "left" << std::endl;
  }
  if (right_) {
    std::cout << "right" << std::endl;
  }
}
void DynamicBufferScene::OnRender() {}
void DynamicBufferScene::OnImGuiRender() {}

DynamicBufferScene::DynamicBufferScene(float width, float height)
 : width_(width), height_(height) {

}

void DynamicBufferScene::OnWindowResizedCallback(int width, int height) {
  size_changed_ = true;
  width_ = width;
  height_ = height;
}

void DynamicBufferScene::OnKeyboardPressCallback(int key, int action) {
  bool* dir = nullptr;
  switch (key){
    case GLFW_KEY_UP:
      dir = &up_;
      break;
    case GLFW_KEY_DOWN:
      dir = &down_;
      break;
    case GLFW_KEY_LEFT:
      dir = &left_;
      break;
    case GLFW_KEY_RIGHT:
      dir = &right_;
      break;
  }

  if (dir == nullptr) {
    return;
  }

  if (action == GLFW_PRESS) {
    *dir = true;
  } else if (action == GLFW_RELEASE) {
    *dir = false;
  }
}
void DynamicBufferScene::OnMouseMoveCallback(double x, double y) {
  if (x < 0 || x > width_ || y < 0 || y > height_) {
    std::cout << "Mouse outside of window, ignoring..." << std::endl;
    return;
  }
  mouse_moved_ = true;
  mouse_x_ = static_cast<float>(x);
  mouse_y_ = static_cast<float>(y);
}
