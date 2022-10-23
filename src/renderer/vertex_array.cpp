//
// Created by Mateusz Palkowski on 21/10/2022.
//

#include "vertex_array.h"

#include "GL/glew.h"
#include "gl_util.h"

VertexArray::VertexArray() { GL_CALL(glGenVertexArrays(1, &renderer_id_)); }
VertexArray::~VertexArray() { GL_CALL(glDeleteVertexArrays(1, &renderer_id_)); }
void VertexArray::AddBuffer(const VertexBuffer& vertex_buffer,
                            const VertexBufferLayout& layout) {
  Bind();
  vertex_buffer.Bind();
  const auto& elements = layout.GetElements();
  unsigned int offset = 0;
  for (unsigned int i = 0; i < elements.size(); ++i) {
    const auto& element = elements[i];
    GL_CALL(glEnableVertexAttribArray(i));
    GL_CALL(glVertexAttribPointer(i, element.count, element.type,
                                  element.normalized, layout.GetStride(),
                                  (const void*)offset));
    offset += element.count * VertexBufferLayout::GetSizeOfType(element.type);
  }
}
void VertexArray::Bind() const { GL_CALL(glBindVertexArray(renderer_id_)); }

void VertexArray::Unbind() const { GL_CALL(glBindVertexArray(0)); }
