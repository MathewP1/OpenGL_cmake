//
// Created by Mateusz Palkowski on 21/10/2022.
//

#include "gl_util.h"

namespace gl {
void ClearError() {
  while (glGetError() != GL_NO_ERROR)
    ;
}

bool Call(const char *function, const char *file, int line) {
  while (GLenum error = glGetError()) {
    std::cout << "[OpenGL Error] (" << error << "): " << function << " " << file
              << ":" << line << std::endl;
    return false;
  }
  return true;
}
}  // namespace gl