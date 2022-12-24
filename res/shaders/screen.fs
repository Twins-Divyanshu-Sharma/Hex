#version 330

out vec4 outColor;

in vec2 fragTex;

uniform sampler2D colorTexture;
uniform sampler2D blurTexture;


void main()
{
    float exposure = 5.0; 
    vec4 color = texture(colorTexture, fragTex);
    
    outColor = color;

    const float gamma = 2.2;
    vec4 hdrColor = texture(colorTexture, fragTex);  
    vec4 bloomColor = texture(blurTexture, fragTex);
    hdrColor += bloomColor; // additive blending
    // tone mapping
    vec4 result = vec4(1.0) - exp(-hdrColor * exposure);
    // also gamma correct while we're at it       
    result = pow(result, vec4(1.0 / gamma));
    outColor = result;
    
}
