#version 330

layout (location = 0) in vec2 objPos;

uniform vec2 position;
uniform float size;
uniform mat4 ortho;

void main()
{
    vec2 worldPos = position + objPos*size;
    gl_Position = ortho * vec4(worldPos, 0, 1);
}
