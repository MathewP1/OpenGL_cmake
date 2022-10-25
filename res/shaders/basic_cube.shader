#shader vertex
#version 410 core

layout(location = 0) in vec3 position_modelspace;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
    v_TexCoord = texCoord;
    gl_Position = u_MVP * vec4(position_modelspace, 1);
}

#shader fragment
#version 410 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
    color = texture(u_Texture, v_TexCoord);
}
