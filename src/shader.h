//
// Created by Mateusz Palkowski on 21/10/2022.
//

#ifndef MINECRAFT_SHADER_H
#define MINECRAFT_SHADER_H

#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

class Shader {
 public:
  Shader(const std::string& file_path);
  ~Shader();

  void Bind() const;
  void Unbind() const;

  void SetUniform1i(const std::string& name, int value);
  void SetUniform4f(const std::string& name, float v0, float v1, float v2,
                    float v4);
  void SetUniformMat4(const std::string& name, const glm::mat4& matrix);


 private:
  unsigned int renderer_id_ = 0;
  std::string file_path_;
  using LocationCacheMap = std::unordered_map<std::string, int>;
  LocationCacheMap location_cache_;

  int GetUniformLocation(const std::string& name);
};

#endif  // MINECRAFT_SHADER_H
