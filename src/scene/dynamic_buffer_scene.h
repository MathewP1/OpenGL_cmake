//
// Created by Mateusz Palkowski on 26/10/2022.
//

#ifndef OPENGL_CMAKE_DYNAMIC_BUFFER_SCENE_H
#define OPENGL_CMAKE_DYNAMIC_BUFFER_SCENE_H

// TODO: 1. Draw a simple cube
// TODO: 2. Implement camera class, update view matrix every frame (every mouse move/keyboard event)
// TODO: 3. Implement dynamic buffer

#include "scene.h"

class DynamicBufferScene : public Scene {
 public:
  DynamicBufferScene(float width, float height);
  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;

  void OnWindowResizedCallback(int width, int height);
  void OnKeyboardPressCallback(int key, int action);
  void OnMouseMoveCallback(double x, double y);

 private:
  float width_, height_;
  bool size_changed_ = false;

  bool up_=false, down_=false, left_=false, right_=false;

  float mouse_x_, mouse_y_;
  bool mouse_moved_ = false;
};

//class Block {
//  struct Gl {
//    float vertices[72];
//    float texture_coordinates[2];
//  };
//};
//class Texture{
//  struct Gl {
//
//  };
//};
//
//class TextureRegistry {
// public:
//  enum class Type {
//    Red,
//    Orange
//  };
//  Texture CreateTexture(Type);
//};
//
//class BlockFactory {
// public:
//  static Block CreateBlock();
//
//private:
//
//
//};
//
//class World {
//  struct Position{
//    int x, y, z;
//  };
//  // world position - > maps to opengl world position
//
//  glm::vec3 getRenderPosition();
//};

// register users of mouse
//class InputHandler {
// public:
//  class Mouse {
//
//  };
//  class Keyboard{
//
//  };
//  class Window {
//
//  };
//};


//class GameLoop {
//  void ProcessEvents() {
//    // process callbacks from event queue
//  }
//  void Upate() {
//    // 1.
//  }
//  void Render();
//};


#endif  // OPENGL_CMAKE_DYNAMIC_BUFFER_SCENE_H
