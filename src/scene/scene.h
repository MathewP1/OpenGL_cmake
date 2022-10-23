//
// Created by Mateusz Palkowski on 23/10/2022.
//

#ifndef OPENGL_CMAKE_SCENE_H
#define OPENGL_CMAKE_SCENE_H

class Scene {
 public:
  virtual ~Scene() = default;
  virtual void OnUpdate(float deltaTime) = 0;
  virtual void OnRender() = 0;
  virtual void OnImGuiRender() = 0;
};

#endif  // OPENGL_CMAKE_SCENE_H
