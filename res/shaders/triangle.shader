#shader vertex
#version 410 core

layout(location = 0) in vec3 position_modelspace;
uniform mat4 u_MVP;
void main()
{
//    gl_Position.xyz = position_modelspace;
//    gl_Position.w = 1.0;
    gl_Position = u_MVP * vec4(position_modelspace, 1);
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;


void main()
{
    color = vec4(1.0, 0, 0, 1);
}