#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexIndex;

uniform sampler2D u_Textures[24];

void main()
{
    int index = int(v_TexIndex);
    color = texture(u_Textures[index], v_TexCoord);
};

