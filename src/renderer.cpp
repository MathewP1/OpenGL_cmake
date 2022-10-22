//
// Created by Mateusz Palkowski on 21/10/2022.
//

#include "renderer.h"

#include "gl_util.h"

void Renderer::Draw(const VertexArray& vertex_array,
                    const IndexBuffer& index_buffer,
                    const Shader& shader) const {
  shader.Bind();
  vertex_array.Bind();
  index_buffer.Bind();

  GL_CALL(glDrawElements(GL_TRIANGLES, index_buffer.GetCount(), GL_UNSIGNED_INT, nullptr));
}
void Renderer::Clear() const {
  GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
}
