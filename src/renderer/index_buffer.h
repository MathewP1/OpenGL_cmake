//
// Created by Mateusz Palkowski on 21/10/2022.
//

#ifndef MINECRAFT_INDEX_BUFFER_H
#define MINECRAFT_INDEX_BUFFER_H

class IndexBuffer {
 private:
  unsigned int renderer_id_;
  unsigned int count_;

 public:
  IndexBuffer(const unsigned int* data, unsigned int count);
  ~IndexBuffer();

  void Bind() const;
  void Unbind() const;

  unsigned int GetCount() const;
};

#endif  // MINECRAFT_INDEX_BUFFER_H
