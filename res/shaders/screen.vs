#version 330

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 tex;

out vec2 fragTex;

void main()
{
    fragTex = vec2(tex);
    gl_Position = vec4(pos, 0.0f, 1.0f);
}
