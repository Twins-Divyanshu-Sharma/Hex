#version 330

out vec4 fragColor;

uniform vec3 color;

void main()
{
    fragColor = vec4(color, 1);
}
