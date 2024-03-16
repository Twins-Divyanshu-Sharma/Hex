
#version 330

layout (location = 0) in vec2 objPos;
layout (location = 1) in vec2 tex;

out vec2 fragTex;

uniform vec2 position;
uniform float scale;
uniform mat4 ortho;

void main()
{
    fragTex = vec2(tex);
    vec2 worldPos = position + objPos*scale;
    gl_Position = ortho * vec4(worldPos, 0, 1);
}
