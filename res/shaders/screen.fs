#version 330

out vec4 outColor;

in vec2 fragTex;

uniform sampler2D colorTexture;


void main()
{
    vec4 color = texture(colorTexture, fragTex);
    outColor = color;
}
