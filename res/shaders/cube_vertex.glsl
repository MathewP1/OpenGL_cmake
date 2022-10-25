#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;

out vec4 v_Color;

uniform mat4 u_MVP;

void main() {
    gl_Position = u_MVP * vec4(position, 1.0f);
    v_Color = color;
}