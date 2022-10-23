//
// Created by Mateusz Palkowski on 23/10/2022.
//

#ifndef OPENGL_CMAKE_SCENE_MENU_H
#define OPENGL_CMAKE_SCENE_MENU_H

#include "scene.h"

class SceneMenu : public Scene {
 public:
  SceneMenu();

  void OnUpdate(float deltaTime) override;
  void OnRender() override;
  void OnImGuiRender() override;
};

#endif  // OPENGL_CMAKE_SCENE_MENU_H
