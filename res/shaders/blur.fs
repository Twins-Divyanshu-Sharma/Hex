#version 330

out vec4 outColor;

in vec2 fragTex;

uniform float horizontal;
uniform sampler2D imageTex;
const float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{
    vec2 texOffset = 1.0/textureSize(imageTex,0); 
    vec4 result = texture(imageTex, fragTex) * weight[0];
    if(horizontal > 0.5)
    {
        for(int i=1; i<5; i++)
        {
            result += texture(imageTex, fragTex + vec2(texOffset.x * i, 0.0)) * weight[i];
            result += texture(imageTex, fragTex - vec2(texOffset.x * i, 0.0)) * weight[i];
        }
    }
    else
    {
         for(int i=1; i<5; i++)
        {
            result += texture(imageTex, fragTex + vec2(0.0, texOffset.y * i)) * weight[i];
            result += texture(imageTex, fragTex - vec2(0.0, texOffset.y * i)) * weight[i];
        }

    }
    outColor = result;
}
