//
// Created by Mateusz Palkowski on 23/10/2022.
//

#ifndef OPENGL_CMAKE_TEXTURED_LOGOS_SCENE_H
#define OPENGL_CMAKE_TEXTURED_LOGOS_SCENE_H

#include <memory>
#include <optional>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/vec3.hpp"
#include "renderer/index_buffer.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "renderer/vertex_array.h"
#include "renderer/vertex_buffer.h"
#include "renderer/vertex_buffer_layout.h"
#include "scene.h"

class TexturedLogosScene : public Scene {
 public:
  TexturedLogosScene();
  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;

 private:
  glm::mat4 projection_ =
      glm::ortho(-200.0f, 200.f, -200.0f, 200.0f, -1.0f, 1.0f);
  glm::mat4 model_view1_{1.0f};
  glm::mat4 model_view2_{1.0f};
  glm::vec3 model_translation1_{-100.0f, -100.0f, 0.0f};
  glm::vec3 model_translation2_{100.0f, 100.0f, 0.0f};
  glm::mat4 view_{1.0f};
  VertexArray vertex_array_;
  std::optional<VertexBuffer> vertex_buffer_;
  std::optional<IndexBuffer> index_buffer_;
  VertexBufferLayout vertex_buffer_layout_;
  std::optional<Shader> shader_;
  std::optional<Texture> texture_;

  Renderer renderer_;
};

#endif  // OPENGL_CMAKE_TEXTURED_LOGOS_SCENE_H
