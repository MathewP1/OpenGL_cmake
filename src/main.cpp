#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "config.h"
#include "gl_util.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "index_buffer.h"
#include "shader.h"
#include "texture.h"
#include "vertex_array.h"
#include "vertex_buffer_layout.h"
#include "renderer.h"

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
  window = glfwCreateWindow(1280, 960, "Hello World", NULL, NULL);
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

  std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "Resources directory: " << RESOURCE_PATH << std::endl;

  // ImGUI init
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  const char* glsl_version = "#version 410";  // should match OpenGL 4.1
  ImGui_ImplOpenGL3_Init(glsl_version);
  ImGui::StyleColorsDark();

  // TODO:
  // 1. Load logo as a texture
  // 2. Display rectangle with texture
  // 3. Transform rectangle with UI
  {
    glm::mat4 projection = glm::ortho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);

    // pos.x, pos.y, texture.x, texture.y
    float vertices[] = {
        0.25f, 0.25f, 0.0f, 0.0f,  // 0
        0.75f, 0.25f, 1.0f, 0.0f,  // 1
        0.75f, 0.75f, 1.0f, 1.0f,  // 2
        0.25f, 0.75f, 0.0f, 1.0f   // 3
    };

    unsigned int indices[] = {0, 1, 2, 2, 3, 0};
    VertexArray vertex_array;
    VertexBuffer vertex_buffer(vertices, 16 * sizeof(float));
    VertexBufferLayout layout;
    layout.PushFloat(2);
    layout.PushFloat(2);
    vertex_array.AddBuffer(vertex_buffer, layout);

    IndexBuffer index_buffer(indices, 6);
    std::string resources(RESOURCE_PATH);
    Shader shader(resources + "shaders/basic.shader");
    shader.Bind();

    Texture texture(resources + "textures/logo.png");
    texture.Bind();

    // pass texture slot to shader
    shader.SetUniform1i("u_Texture", 0);
    Renderer renderer;

    glm::vec3 values(0.0f, 0.0f, 0.0f);
    glm::mat4 view(1.0f); // identity matrix for view

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
      /* Render here */
      renderer.Clear();

      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();


      shader.Bind();
      glm::mat4 model = glm::translate(glm::mat4(1.0f), values);
      glm::mat4 mvp = projection * view * model;
      shader.SetUniformMat4("u_MVP", mvp);

      renderer.Draw(vertex_array, index_buffer, shader);

      {
        ImGui::SliderFloat3(
            "float", &values.x, -1.0f,
            1.0f);  // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                    1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
      }

      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      /* Swap front and back buffers */
      glfwSwapBuffers(window);

      /* Poll for and process events */
      glfwPollEvents();
    }
  }
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
  glfwTerminate();
  return 0;
}