//
// Created by Mateusz Palkowski on 23/10/2022.
//
#include "triangle_scene.h"

#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include "config.h"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"

TriangleScene::TriangleScene(float width, float height)
    : projection_(glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f)),
      view_(1.0f),
      model_(1.0f) {
  float vertices[] = {
      -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
  };
  unsigned int indices[] = {0, 1, 2};
  vertex_buffer_.emplace(vertices, 9 * sizeof(float));
  vertex_buffer_layout_.PushFloat(3);
  vertex_array_.AddBuffer(vertex_buffer_.value(), vertex_buffer_layout_);

  index_buffer_.emplace(indices, 3);
  std::string resources(RESOURCE_PATH);
  shader_.emplace(resources + "shaders/triangle.shader");
  shader_->Bind();
}

void TriangleScene::OnUpdate(float deltaTime) {
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

void TriangleScene::OnRender() {
  shader_->Bind();
  auto mvp = projection_ * view_ * model_;
  shader_->SetUniformMat4("u_MVP", mvp);
  renderer_.Draw(vertex_array_, index_buffer_.value(), shader_.value());
}

void TriangleScene::OnImGuiRender() {
  ImGui::SliderFloat3("view translation", &translation_.x, -10.0f, 10.0f);
  ImGui::SliderFloat3("view scale", &scale_.x, -10.0f, 10.0f);
  ImGui::SliderFloat("rotation x", &rotate_x_, -10.0f, 10.0f);
  ImGui::SliderFloat("rotation y", &rotate_y_, -1.0f, 1.0f);
  ImGui::SliderFloat("rotation z", &rotate_z_, -10.0f, 10.0f);
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
