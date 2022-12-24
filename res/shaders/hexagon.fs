#version 330

layout (location=0) out vec4 fragColor;
layout (location=1) out vec4 brightColor;

uniform vec4 color;
uniform float neon;

void main()
{
    fragColor = vec4(color);
    
    if(neon >= 0.5)
        brightColor = vec4(color);
    else
        brightColor = vec4(0,0,0,1);

}
