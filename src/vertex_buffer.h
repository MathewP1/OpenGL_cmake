//
// Created by Mateusz Palkowski on 21/10/2022.
//

#ifndef MINECRAFT_VERTEX_BUFFER_H
#define MINECRAFT_VERTEX_BUFFER_H

class VertexBuffer {
 private:
  unsigned int renderer_id_;

 public:
  VertexBuffer(const void* data, unsigned int size);
  ~VertexBuffer();

  void Bind() const;
  void Unbind() const;
};

#endif  // MINECRAFT_VERTEX_BUFFER_H
