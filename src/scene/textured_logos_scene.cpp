//
// Created by Mateusz Palkowski on 23/10/2022.
//

#include "textured_logos_scene.h"

#include <iostream>

#include "config.h"
#include "imgui/imgui.h"

TexturedLogosScene::TexturedLogosScene() {
  float vertices[] = {
      -50.0f, -50.0f, 0.0f, 0.0f,  // 0
      50.0f,  -50.0f, 1.0f, 0.0f,  // 1
      50.0f,  50.0f,  1.0f, 1.0f,  // 2
      -50.0f, 50.0f,  0.0f, 1.0f   // 3
  };
  unsigned int indices[] = {0, 1, 2, 2, 3, 0};

  vertex_buffer_.emplace(vertices, 16 * sizeof(float));
  vertex_buffer_layout_.PushFloat(2);
  vertex_buffer_layout_.PushFloat(2);
  vertex_array_.AddBuffer(vertex_buffer_.value(), vertex_buffer_layout_);

  index_buffer_.emplace(indices, 6);
  std::string resources(RESOURCE_PATH);
  shader_.emplace(resources + "shaders/basic.shader");
  shader_->Bind();

  texture_.emplace(resources + "textures/logo.png");
  texture_->Bind();
  shader_->SetUniform1i("u_Texture", 0);
}

void TexturedLogosScene::OnUpdate(float deltaTime) {
  model_view1_ = view_ * glm::translate(glm::mat4(1.0f), model_translation1_);
  model_view2_ = view_ * glm::translate(glm::mat4(1.0f), model_translation2_);
}
void TexturedLogosScene::OnRender() {
  shader_->Bind();
  auto mvp = projection_ * model_view1_;
  shader_->SetUniformMat4("u_MVP", mvp);
  renderer_.Draw(vertex_array_, index_buffer_.value(), shader_.value());

  mvp = projection_ * model_view2_;
  shader_->SetUniformMat4("u_MVP", mvp);
  renderer_.Draw(vertex_array_, index_buffer_.value(), shader_.value());
}
void TexturedLogosScene::OnImGuiRender() {
  ImGui::SliderFloat3("float1", &model_translation1_.x, -100.0f, 100.0f);
  ImGui::SliderFloat3("float2", &model_translation2_.x, -100.0f, 100.0f);
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}