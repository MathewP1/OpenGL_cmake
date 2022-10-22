//
// Created by Mateusz Palkowski on 21/10/2022.
//

#include "texture.h"

#include <filesystem>

#include "stb_image.h"

#include "gl_util.h"

Texture::Texture(const std::string& file_path)
    : file_path_(file_path) {

  stbi_set_flip_vertically_on_load(1);
  local_buffer_ = stbi_load(file_path.c_str(), &width_, &height_, &bpp_, 0);

  if (!local_buffer_) {
    std::cout << "Failed to load buffer!";
  }

//  for (int i = 0; i < width_; ++i) {
//    for (int )
//  }




  GL_CALL(glGenTextures(1, &renderer_id_));
  GL_CALL(glBindTexture(GL_TEXTURE_2D, renderer_id_));

  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, local_buffer_));

  Unbind();

  if (local_buffer_) {
    stbi_image_free(local_buffer_);
    local_buffer_ = nullptr;
  }
}

Texture::~Texture() {
  GL_CALL(glDeleteTextures(1, &renderer_id_));
}

void Texture::Bind(unsigned int slot) const {
  GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
  GL_CALL(glBindTexture(GL_TEXTURE_2D, renderer_id_));
}

void Texture::Unbind() const {
  GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}
int Texture::GetWidth() const { return width_; }
int Texture::GetHeight() const { return height_; }
