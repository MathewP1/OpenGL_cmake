//
// Created by Mateusz Palkowski on 21/10/2022.
//

#ifndef MINECRAFT_TEXTURE_H
#define MINECRAFT_TEXTURE_H

#include <string>

#include "renderer.h"

class Texture {
 public:
  Texture(const std::string& file_path);
  ~Texture();

  void Bind(unsigned int slot = 0) const;
  void Unbind() const;

  int GetWidth() const;
  int GetHeight() const;


 private:
  unsigned int renderer_id_ = 0;
  std::string file_path_;
  unsigned char* local_buffer_ = nullptr;
  int width_ = 0, height_ = 0, bpp_ = 0;
};

#endif  // MINECRAFT_TEXTURE_H
