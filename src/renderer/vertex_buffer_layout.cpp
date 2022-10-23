//
// Created by Mateusz Palkowski on 21/10/2022.
//

#include "vertex_buffer_layout.h"

VertexBufferLayout::VertexBufferLayout() {}
const std::vector<VertexBufferLayout::Element>&
VertexBufferLayout::GetElements() const {
  return elements_;
}
const unsigned int VertexBufferLayout::GetStride() const { return stride_; }
unsigned int VertexBufferLayout::GetSizeOfType(unsigned int type) {
  switch (type) {
    case GL_FLOAT:
      return 4;
    case GL_UNSIGNED_INT:
      return 4;
  }
  return 0;
}
void VertexBufferLayout::PushFloat(unsigned int count) {
  elements_.push_back({GL_FLOAT, count, GL_FALSE});
  stride_ += GetSizeOfType(GL_FLOAT) * count;
}
void VertexBufferLayout::PushUInt(unsigned int count) {
  elements_.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
  stride_ += GetSizeOfType(GL_UNSIGNED_INT) * count;
}
