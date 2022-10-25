//
// Created by Mateusz Palkowski on 25/10/2022.
//
#include "textured_cube_scene.h"

#include "config.h"
#include "renderer/gl_util.h"
#include <fstream>
#include <sstream>
#include <string>
#include "glm/gtc/matrix_transform.hpp"

TexturedCubeScene::TexturedCubeScene(float width, float height)
    : width_(width), height_(height),
      projection_(glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f)),
      view_(glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0))),
      model_(1.0f){
  float vertices[] = {
      -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
      1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 1.0f, 1.0f,1.0f, 0.0f, 0.0f, 1.0f,
      -1.0f, 1.0f, 1.0f,0.0f, 0.0f, 1.0f, 1.0f,
      -1.0f, -1.0f, -1.0f,0.0f, 1.0f, 1.0f, 1.0f,
      1.0f, -1.0f, -1.0f,1.0f, 1.0f, 0.0f, 1.0f,
      1.0f, 1.0f, -1.0f,0.7f, 0.5f, 0.4f, 1.0f,
      -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
  };

  unsigned int indices[] = {
      // front
      0, 1, 2,
      2, 3, 0,
      // right
      1, 5, 6,
      6, 2, 1,
      // back
      7, 6, 5,
      5, 4, 7,
      // left
      4, 0, 3,
      3, 7, 4,
      // bottom
      4, 5, 1,
      1, 0, 4,
      // top
      3, 2, 6,
      6, 7, 3
  };

  // generate vertex buffer object - VBO
  GL_CALL(glGenVertexArrays(1, &vbo_));
  GL_CALL(glBindVertexArray(vbo_));

  // generate vertex buffer
  GL_CALL(glGenBuffers(1, &vb_));
  GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vb_));
  GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

  GL_CALL(glEnableVertexAttribArray(0));
  GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), nullptr));

  GL_CALL(glEnableVertexAttribArray(1));
  GL_CALL(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const void*)(3 * sizeof(float))));

  // generate index buffer
  GL_CALL(glGenBuffers(1, &ib_));
  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_));
  GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

  std::string resources(RESOURCE_PATH);
  shader_ = gl::CreateShader(resources + "shaders/cube_vertex.glsl", resources + "shaders/cube_fragment.glsl");
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
}

void TexturedCubeScene::OnUpdate(float deltaTime) {
  // maybe make window scalable - some glfw event?
  if (size_changed_) {
    // TODO: recalculate the projection matrix (or view?)
    projection_ = glm::perspective(glm::radians(45.0f), width_ / height_, 0.1f, 100.0f);
  }

  model_ = glm::rotate(model_, 1 * deltaTime, glm::vec3(0, 1, 0));
}

void TexturedCubeScene::OnRender() {
  GL_CALL(glBindVertexArray(vbo_));
  GL_CALL(glUseProgram(shader_));


  auto mvp = projection_ * view_ * model_;
  unsigned int loc = glGetUniformLocation(shader_, "u_MVP");
  GL_CALL(glUniformMatrix4fv(loc, 1, GL_FALSE, &mvp[0][0]));

  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib_));
  int size;
  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
  GL_CALL(glDrawElements(GL_TRIANGLES, size / sizeof(unsigned  int), GL_UNSIGNED_INT, nullptr));
}
void TexturedCubeScene::OnImGuiRender() {}

void TexturedCubeScene::OnWindowResizedCallback(int width, int height) {
  width_ = static_cast<float>(width);
  height_ = static_cast<float>(height);
  size_changed_ = true;
}
