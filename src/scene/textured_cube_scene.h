//
// Created by Mateusz Palkowski on 25/10/2022.
//

#ifndef OPENGL_CMAKE_TEXTURED_CUBE_SCENE_H
#define OPENGL_CMAKE_TEXTURED_CUBE_SCENE_H

#include "scene.h"
#include "glm/glm.hpp"

class TexturedCubeScene : public Scene {
 public:
  TexturedCubeScene(float width, float height);

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;
  void OnWindowResizedCallback(int width, int height);

 private:
  glm::mat4 projection_, view_, model_;
  glm::mat4 view_translation_{1.0f}, view_scale_{1.0f}, view_rotation_{1.0f};
  glm::vec3 translation_{0.0f, 0.0f, -2.5f}, scale_{1.0f};
  float rotate_x_ = 0, rotate_y_ = 0, rotate_z_ = 0;

  float width_, height_;
  bool size_changed_ = false;
  unsigned int vb_, ib_, vbo_, shader_, texture_, texture1_;
  bool amogus_ = false;
};

#endif  // OPENGL_CMAKE_TEXTURED_CUBE_SCENE_H
