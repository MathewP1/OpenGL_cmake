//
// Created by Mateusz Palkowski on 21/10/2022.
//

#ifndef MINECRAFT_RENDERER_H
#define MINECRAFT_RENDERER_H

#include "GL/glew.h"
#include "index_buffer.h"
#include "shader.h"
#include "vertex_array.h"

// TODO: Renderer should take a Material instead of Shader
// Material is a set of uniforms and a shader - eg. Metallic etc
class Renderer {
 public:
  void Draw(const VertexArray& vertex_array, const IndexBuffer& index_buffer,
            const Shader& shader) const;
  void Clear() const;
};

#endif  // MINECRAFT_RENDERER_H
