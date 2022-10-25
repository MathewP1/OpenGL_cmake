//
// Created by Mateusz Palkowski on 24/10/2022.
//
#include "cube_scene.h"

#include "config.h"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"

CubeScene::CubeScene(float width, float height)
    : projection_(
          glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f)),
      view_(glm::lookAt(
          glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
          glm::vec3(0,0,0), // and looks at the origin
          glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
          )),
      model_(1.0f) {
  float vertices[] = {
      -1.0f,-1.0f, -1.0f, 0.0f,  0.0f,
      1.0f,-1.0f, -1.0f,1.0f,  0.0f,
      1.0f, 1.0f, -1.0f, 1.0,  1.0f,
      -1.0f,1.0f,  -1.0f, 0.0f,  1.0f,
      -1.0f, -1.0f,1.0f, 0.0f,  0.0f,
      1.0f, -1.0f, 1.0f, 1.0f,  0.0f,
      1.0f, 1.0f, 1.0f, 1.0,  1.0f,
      -1.0f,1.0f, 1.0f, 0.0f,  1.0f
  };

  unsigned int indices[] = {
      0, 1, 2, 2, 3, 0,
      1, 5, 6, 6, 2, 1,
      5, 6, 7, 7, 4, 5,
      4, 7, 3, 3, 0, 4,
      0, 1, 5, 5, 4, 0,
      3, 2, 6, 6, 7, 3
  };


  vertex_buffer_.emplace(vertices, sizeof(float) * 40);
  vertex_buffer_layout_.PushFloat(3);
  vertex_buffer_layout_.PushFloat(2);
  vertex_array_.AddBuffer(vertex_buffer_.value(), vertex_buffer_layout_);

  index_buffer_.emplace(indices, 36);
  std::string resources(RESOURCE_PATH);
  shader_.emplace(resources + "shaders/basic_cube.shader");
  shader_->Bind();

  texture_.emplace(resources + "textures/logo.png");
  texture_->Bind();
  shader_->SetUniform1i("u_Texture", 0);

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

void CubeScene::OnUpdate(float deltaTime) {
  view_translation_ = glm::translate(glm::mat4(1.0f), translation_);
  view_scale_ = glm::scale(glm::mat4(1.0f), scale_);

  glm::vec3 rotation_x_axis(1.0f, 0.0f, 0.0f);
  glm::vec3 rotation_y_axis(0.0f, 1.0f, 0.0f);
  glm::vec3 rotation_z_axis(0.0f, 0.0f, 1.0f);
  auto x = glm::rotate(glm::mat4(1.0f), rotate_x_, rotation_x_axis);
  auto y = glm::rotate(x, rotate_y_, rotation_y_axis);
  view_rotation_ = glm::rotate(y, rotate_z_, rotation_z_axis);
  view_ = view_translation_ * view_rotation_ * view_scale_;
}

void CubeScene::OnRender() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shader_->Bind();
  auto mvp = projection_ * view_ * model_;
  shader_->SetUniformMat4("u_MVP", mvp);
  renderer_.Draw(vertex_array_, index_buffer_.value(), shader_.value());
}

void CubeScene::OnImGuiRender() {
  ImGui::SliderFloat3("view translation", &translation_.x, -10.0f, 10.0f);
  ImGui::SliderFloat3("view scale", &scale_.x, -10.0f, 10.0f);
  ImGui::SliderFloat("rotation x", &rotate_x_, -90.0f, 90.0f);
  ImGui::SliderFloat("rotation y", &rotate_y_, -90.0f, 90.0f);
  ImGui::SliderFloat("rotation z", &rotate_z_, -90.0f, 90.0f);
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
