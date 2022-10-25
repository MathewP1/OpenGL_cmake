#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "config.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "renderer/gl_util.h"
#include "renderer/renderer.h"
#include "scene/cube_scene.h"
#include "scene/textured_cube_scene.h"
#include "scene/triangle_scene.h"


int main(void) {
  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit()) return -1;

  // Set lowest possible version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // Set to core profile - necessary on MacOS
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  float window_width = 1500;
  float window_height = 1200;
  window =
      glfwCreateWindow(window_width, window_height, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  // Init glew to link to OpenGL implementation
  if (glewInit() != GLEW_OK) {
    std::cout << "Error!" << std::endl;
  }

  GL_CALL(glEnable(GL_BLEND));
  GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
  GL_CALL(glClearColor(0.2f, 0.02f, 0.2f, 1.0f));

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "Resources directory: " << RESOURCE_PATH << std::endl;

  // ImGUI init
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  const char* glsl_version = "#version 410";  // should match OpenGL 4.1
  ImGui_ImplOpenGL3_Init(glsl_version);
  ImGui::StyleColorsDark();

  TexturedCubeScene scene(window_width, window_height);

  glfwSetWindowUserPointer(window, &scene);
  glfwSetFramebufferSizeCallback(
      window, [](GLFWwindow* window, int width, int height) {
        auto& scene =
            *static_cast<TexturedCubeScene*>(glfwGetWindowUserPointer(window));
        scene.OnWindowResizedCallback(width, height);
      });
//  TriangleScene scene(window_width, window_height);


  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    /* Render here */
//    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    scene.OnUpdate(1.0f / 60.0f);
    scene.OnRender();
    ImGui::Begin("Scene");
    scene.OnImGuiRender();
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwTerminate();
  return 0;
}