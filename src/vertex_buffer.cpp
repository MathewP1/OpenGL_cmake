//
// Created by Mateusz Palkowski on 21/10/2022.
//
#include "vertex_buffer.h"

#include "GL/glew.h"
#include "gl_util.h"

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
  GL_CALL(glGenBuffers(1, &renderer_id_));
  GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, renderer_id_));
  GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer() { GL_CALL(glDeleteBuffers(1, &renderer_id_)); }

void VertexBuffer::Bind() const {
  GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, renderer_id_));
}

void VertexBuffer::Unbind() const { GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); }
