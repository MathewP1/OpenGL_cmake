cmake_minimum_required(VERSION 3.23)
project(OpenGL_cmake
        VERSION 0.1
        DESCRIPTION "Template for cross-platform OpenGL cmake project"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include third-party libs
add_subdirectory(third_party/glew)
add_subdirectory(third_party/glfw)
add_subdirectory(third_party/stb_image)
add_subdirectory(third_party/glm)
add_subdirectory(third_party/imgui/imgui)

# Generate config.h
set(RESOURCE_PATH "${PROJECT_SOURCE_DIR}/res/")
configure_file(src/config.h.in src/config.h)

set(SOURCE_FILES
        "src/renderer/gl_util.h" "src/renderer/gl_util.cpp"
        "src/renderer/index_buffer.h" "src/renderer/index_buffer.cpp"
        "src/renderer/renderer.h" "src/renderer/renderer.cpp"
        "src/renderer/shader.h" "src/renderer/shader.cpp"
        "src/renderer/texture.h" "src/renderer/texture.cpp"
        "src/renderer/vertex_array.h" "src/renderer/vertex_array.cpp"
        "src/renderer/vertex_buffer.h" "src/renderer/vertex_buffer.cpp"
        "src/renderer/vertex_buffer_layout.h" "src/renderer/vertex_buffer_layout.cpp"
        src/scene/scene.h
        src/scene/scene_menu.h src/scene/scene_menu.cpp
        src/scene/textured_logos_scene.h src/scene/textured_logos_scene.cpp src/scene/triangle_scene.h src/scene/triangle_scene.cpp src/scene/cube_scene.h src/scene/cube_scene.cpp src/scene/textured_cube_scene.h src/scene/textured_cube_scene.cpp src/scene/dynamic_buffer_scene.h src/scene/dynamic_buffer_scene.cpp)

add_executable(OpenGL_cmake src/main.cpp ${SOURCE_FILES})

target_include_directories(OpenGL_cmake
        PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/src"
        PRIVATE "src"
        PRIVATE "third_party/stb_image"
        PRIVATE "third_party/imgui")

target_link_libraries(OpenGL_cmake
        PRIVATE glfw
        PRIVATE libglew_static
        glm
        stb_image
        imgui)