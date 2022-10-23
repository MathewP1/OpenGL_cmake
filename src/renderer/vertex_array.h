//
// Created by Mateusz Palkowski on 21/10/2022.
//

#ifndef MINECRAFT_VERTEX_ARRAY_H
#define MINECRAFT_VERTEX_ARRAY_H

#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

class VertexArray {
 public:
  VertexArray();
  ~VertexArray();

  void Bind() const;
  void Unbind() const;

  void AddBuffer(const VertexBuffer& vertex_buffer,
                 const VertexBufferLayout& layout);

 private:
  unsigned int renderer_id_;
};

#endif  // MINECRAFT_VERTEX_ARRAY_H
