//
// Created by Mateusz Palkowski on 21/10/2022.
//
#include "shader.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "GL/glew.h"
#include "gl_util.h"

namespace {
struct ShaderSource {
  std::string vertex;
  std::string fragment;
};

ShaderSource ParseShaders(const std::string &filename) {
  std::ifstream shader_fs(filename);
  std::string line;

  std::stringstream vertex, fragment;
  std::stringstream *current = nullptr;
  while (getline(shader_fs, line)) {
    if (line.find("#shader") != std::string::npos) {
      if (line.find("vertex") != std::string::npos) {
        current = &vertex;
      } else if (line.find("fragment") != std::string::npos) {
        current = &fragment;
      } else {
        current = nullptr;
      }
    } else {
      if (current) {
        *current << line << '\n';
      }
    }
  }

  return {vertex.str(), fragment.str()};
}

unsigned int CompileShader(unsigned int type, const std::string &source) {
  unsigned int id = glCreateShader(type);
  const char *src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

    char *message = new char[length];
    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "Failed to compile shader!" << std::endl;
    std::cout << message << std::endl;
    delete[] message;
    return 0;
  }
  return id;
}

unsigned int CreateShader(const std::string &vertex_shader,
                          const std::string &fragment_shader) {
  unsigned int program = glCreateProgram();
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex_shader);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment_shader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}
}  // namespace

Shader::Shader(const std::string &file_path) : file_path_(file_path) {
  ShaderSource source = ParseShaders(file_path_);
  renderer_id_ = CreateShader(source.vertex, source.fragment);
}

Shader::~Shader() { GL_CALL(glDeleteProgram(renderer_id_)); }

void Shader::Bind() const { GL_CALL(glUseProgram(renderer_id_)); }

void Shader::Unbind() const { GL_CALL(glUseProgram(0)); }

void Shader::SetUniform1i(const std::string &name, int value) {
  GL_CALL(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2,
                          float v3) {
  GL_CALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4(const std::string &name, const glm::mat4 &matrix) {
  GL_CALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string &name) {
  if (location_cache_.find(name) != location_cache_.end()) {
    return location_cache_[name];
  }

  GL_CALL(int location = glGetUniformLocation(renderer_id_, name.c_str()));
  if (location == -1) {
    std::cout << "Warning: uniform: " << name << " doesn't exist!" << std::endl;
  }
  location_cache_[name] = location;
  return location;
}
