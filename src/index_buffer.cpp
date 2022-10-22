//
// Created by Mateusz Palkowski on 21/10/2022.
//
#include "index_buffer.h"

#include "GL/glew.h"
#include "gl_util.h"

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count)
    : count_(count) {
  GL_CALL(glGenBuffers(1, &renderer_id_));
  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id_));
  GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int),
                       data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() { GL_CALL(glDeleteBuffers(1, &renderer_id_)); }

void IndexBuffer::Bind() const {
  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer_id_));
}

void IndexBuffer::Unbind() const {
  GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
unsigned int IndexBuffer::GetCount() const { return count_; }
