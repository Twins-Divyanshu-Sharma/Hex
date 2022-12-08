#version 330

out vec4 outColor;

in vec2 fragTex;

uniform sampler2D atlas;
uniform vec2 index;
uniform vec3 textColor;
uniform vec2 size;
uniform float debug;

void main()
{
    if(debug < 0.0)
    {
        outColor = vec4(1,0,0,1);
        return;
    }
    
    vec2 steps = vec2(0.0625,0.125);    
    vec2 correctedIndex = vec2(index.x,7.0 - index.y); 
    
    vec2 sampleCoords = steps*correctedIndex + fragTex*size;
    vec4 color = texture(atlas, sampleCoords);

    //vec4 color = texture(atlas, fragTex);
    outColor = color;
    outColor.rgb *= textColor;

    if(outColor.a < 0.25)
        discard;

}


