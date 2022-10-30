//
// Created by Mateusz Palkowski on 25/10/2022.
//
#include "textured_cube_scene.h"

#include <fstream>
#include <sstream>
#include <string>

#include "config.h"
#include "glm/gtc/matrix_transform.hpp"
#include "renderer/gl_util.h"
#include "stb_image.h"
#include "imgui/imgui.h"

TexturedCubeScene::TexturedCubeScene(float width, float height)
    : width_(width), height_(height),
      projection_(glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f)),
      view_(glm::lookAt(glm::vec3(3, 0, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))),
      model_(1.0f){
  float vertices[] = {
      // front
      -1.0, -1.0,  0, 0.0, 0.0,
      1.0, -1.0,  0, 1.0, 0.0,
      1.0,  1.0,  0, 1.0, 1.0,
      -1.0,  1.0,  0, 0.0, 1.0,
      // top
      -1.0,  1.0,  0, 0.0, 0.0,
      1.0,  1.0,  0, 1.0, 0.0,
      1.0,  1.0, -1.0, 1.0, 1.0,
      -1.0,  1.0, -1.0, 0.0, 1.0,
      // back
      1.0, -1.0, -1.0, 0.0, 0.0,
      -1.0, -1.0, -1.0, 1.0, 0.0,
      -1.0,  1.0, -1.0, 1.0, 1.0,
      1.0,  1.0, -1.0, 0.0, 1.0,
      // bottom
      -1.0, -1.0, -1.0, 0.0, 0.0,
      1.0, -1.0, -1.0, 1.0, 0.0,
      1.0, -1.0,  0, 1.0, 1.0,
      -1.0, -1.0,  0, 0.0, 1.0,
      // left
      -1.0, -1.0, -1.0, 0.0, 0.0,
      -1.0, -1.0,  0, 1.0, 0.0,
      -1.0,  1.0,  0, 1.0, 1.0,
      -1.0,  1.0, -1.0, 0.0, 1.0,
      // right
      1.0, -1.0,  0, 0.0, 0.0,
      1.0, -1.0, -1.0, 1.0, 0.0,
      1.0,  1.0, -1.0, 1.0, 1.0,
      1.0,  1.0,  0, 0.0, 1.0,
  };

  unsigned int indices[] = {
      // front
      0,  1,  2,
      2,  3,  0,
      // top
      4,  5,  6,
      6,  7,  4,
      // back
      8,  9, 10,
      10, 11,  8,
      // bottom
      12, 13, 14,
      14, 15, 12,
      // left
      16, 17, 18,
      18, 19, 16,
      // right
      20, 21, 22,
      22, 23, 20,
  };

  // generate vertex buffer object - VBO
  GL_CALL(glGenVertexArrays(1, &vbo_));
  GL_CALL(glBindVertexArray(vbo_));

  // generate vertex buffer
  GL_CALL(glGenBuffers(1, &vb_));
  GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vb_));
  GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

  GL_CALL(glEnableVertexAttribArray(0));
  GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr));

  GL_CALL(glEnableVertexAttribArray(1));
  GL_CALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (const void*)(3 * sizeof(float))));

  // generate index buffer
  GL_CALL(glGenBuffers(1, &ib_));
  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_));
  GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

  std::string resources(RESOURCE_PATH);
  shader_ = gl::CreateShader(resources + "shaders/textured_cube_vertex.glsl", resources + "shaders/textured_cube_fragment.glsl");

  // Load textures
  std::string texture_path(resources + "textures/logo.png");
  stbi_set_flip_vertically_on_load(1);
  int tex_width, tex_height, bpp;
  unsigned char* local_buffer = stbi_load(texture_path.c_str(), &tex_width, &tex_height, &bpp, 4);
  if (!local_buffer) {
    std::cout << "Couldn't load texture to memory" << std::endl;
  }

  GL_CALL(glActiveTexture(GL_TEXTURE0));
  GL_CALL(glGenTextures(1, &texture_));
  GL_CALL(glBindTexture(GL_TEXTURE_2D, texture_));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer));

  if (local_buffer) {
    stbi_image_free(local_buffer);
    local_buffer = nullptr;
  }

  texture_path = resources + "textures/amogus.png";
  local_buffer = stbi_load(texture_path.c_str(), &tex_width, &tex_height, &bpp, 4);
  if (!local_buffer) {
    std::cout << "Couldn't load texture to memory" << std::endl;
  }
  GL_CALL(glActiveTexture(GL_TEXTURE1));
  GL_CALL(glGenTextures(1, &texture1_));
  GL_CALL(glBindTexture(GL_TEXTURE_2D, texture1_));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
  GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer));


  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
}

void TexturedCubeScene::OnUpdate(float deltaTime) {
  // maybe make window scalable - some glfw event?
  if (size_changed_) {
    // TODO: recalculate the projection matrix (or view?)
    projection_ = glm::perspective(glm::radians(45.0f), width_ / height_, 0.1f, 100.0f);
  }
  view_translation_ = glm::translate(glm::mat4(1.0f), translation_);
  view_scale_ = glm::scale(glm::mat4(1.0f), scale_);
  glm::vec3 rotation_x_axis(1.0f, 0.0f, 0.0f);
  glm::vec3 rotation_y_axis(0.0f, 1.0f, 0.0f);
  glm::vec3 rotation_z_axis(0.0f, 0.0f, 1.0f);
  auto x = glm::rotate(glm::mat4(1.0f), rotate_x_, rotation_x_axis);
  auto y = glm::rotate(x, rotate_y_, rotation_y_axis);
  view_rotation_ = glm::rotate(y, rotate_z_, rotation_z_axis);
  view_ = view_translation_ * view_rotation_ * view_scale_;
//  float ang_speed = 15;
//  model_ *= glm::rotate(glm::mat4(1.0f), glm::radians(ang_speed) * deltaTime, glm::vec3(1, 0, 0)) *
//            glm::rotate(glm::mat4(1.0f), glm::radians(ang_speed+5) * deltaTime, glm::vec3(0, 1, 0)) *
//            glm::rotate(glm::mat4(1.0f), glm::radians(ang_speed+10) * deltaTime, glm::vec3(0, 0, 1));
}

void TexturedCubeScene::OnRender() {
  GL_CALL(glBindVertexArray(vbo_));
  GL_CALL(glUseProgram(shader_));

  int slot = (amogus_) ? 1 : 0;
  GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
  unsigned int texture_uniform = glGetUniformLocation(shader_, "u_Texture");
  GL_CALL(glUniform1i(texture_uniform, slot));

  auto mvp = projection_ * view_ * model_;
  unsigned int loc = glGetUniformLocation(shader_, "u_MVP");
  GL_CALL(glUniformMatrix4fv(loc, 1, GL_FALSE, &mvp[0][0]));

  if (wireframe_) {
    GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
  } else {
    GL_CALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
  }

  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_));
  int size;
  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
  GL_CALL(glDrawElements(GL_TRIANGLES, size / sizeof(unsigned  int), GL_UNSIGNED_INT, nullptr));
}
void TexturedCubeScene::OnImGuiRender() {
  ImGui::Checkbox("Amogus mode", &amogus_);
  ImGui::Checkbox("wireframe", &wireframe_);

  ImGui::SliderFloat3("view translation", &translation_.x, -10.0f, 10.0f);
  ImGui::SliderFloat3("view scale", &scale_.x, -10.0f, 10.0f);
  ImGui::SliderFloat("rotation x", &rotate_x_, -10.0f, 10.0f);
  ImGui::SliderFloat("rotation y", &rotate_y_, -1.0f, 1.0f);
  ImGui::SliderFloat("rotation z", &rotate_z_, -10.0f, 10.0f);
}

void TexturedCubeScene::OnWindowResizedCallback(int width, int height) {
  width_ = static_cast<float>(width);
  height_ = static_cast<float>(height);
  size_changed_ = true;
}
