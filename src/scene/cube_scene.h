//
// Created by Mateusz Palkowski on 24/10/2022.
//

#ifndef OPENGL_CMAKE_CUBE_SCENE_H
#define OPENGL_CMAKE_CUBE_SCENE_H

#include "renderer/index_buffer.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "renderer/vertex_array.h"
#include "renderer/vertex_buffer.h"
#include "renderer/vertex_buffer_layout.h"
#include "scene.h"

class CubeScene : public Scene {
 public:
  CubeScene(float width, float height);
  ~CubeScene() = default;

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;

 private:
  glm::mat4 projection_, view_, model_;
  glm::mat4 view_translation_{1.0f}, view_scale_{1.0f}, view_rotation_{1.0f};
  glm::vec3 translation_{0.0f, 0.0f, -2.5f}, scale_{1.0f};
  float rotate_x_ = 0, rotate_y_ = 0, rotate_z_ = 0;
  VertexArray vertex_array_;
  std::optional<VertexBuffer> vertex_buffer_;
  std::optional<IndexBuffer> index_buffer_;
  VertexBufferLayout vertex_buffer_layout_;
  std::optional<Shader> shader_;
  std::optional<Texture> texture_;

  Renderer renderer_;
};

#endif  // OPENGL_CMAKE_CUBE_SCENE_H
