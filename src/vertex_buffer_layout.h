//
// Created by Mateusz Palkowski on 21/10/2022.
//

#ifndef MINECRAFT_VERTEX_BUFFER_LAYOUT_H
#define MINECRAFT_VERTEX_BUFFER_LAYOUT_H

#include <vector>

#include "GL/glew.h"

class VertexBufferLayout {
 public:
  struct Element {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
  };

  VertexBufferLayout();


  const std::vector<Element>& GetElements() const;
  const unsigned int GetStride() const;

  static unsigned int GetSizeOfType(unsigned int type);

  void PushFloat(unsigned int count);
  void PushUInt(unsigned int count);

 private:
  std::vector<Element> elements_;
  unsigned int stride_ = 0;
};

#endif  // MINECRAFT_VERTEX_BUFFER_LAYOUT_H
