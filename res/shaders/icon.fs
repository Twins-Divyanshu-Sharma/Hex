#version 330

layout (location=0) out vec4 outColor;

in vec2 fragTex;

uniform sampler2D image;
uniform vec3 textColor;
uniform vec2 imageWH;

uniform int iconState;

vec4 neonImage()
{

  vec2 step = vec2(1.0/imageWH.x, 1.0/imageWH.y);
  step = 4.0*step;
  vec2 offsets[9] = vec2[](
      vec2(-step.x,  step.y), // top-left
      vec2( 0.0f,    step.y), // top-center
      vec2( step.x,  step.y), // top-right
      vec2(-step.x,  0.0f),   // center-left
      vec2( 0.0f,    0.0f),   // center-center
      vec2( step.x,  0.0f),   // center-right
      vec2(-step.x, -step.y), // bottom-left
      vec2( 0.0f,   -step.x), // bottom-center
      vec2( step.x, -step.y)  // bottom-right    
  );

  float kernel[9] = float[](
      1, 1, 1,
      1,  -8, 1,
      1, 1, 1
  );
  
  vec4 sampleTex[9];
  vec3 col = vec3(0);
  
  float idealAlpha = 0.0;
  for(int i = 0; i < 9; i++)
  {
      sampleTex[i] = (texture(image, fragTex + offsets[i]));
      col += sampleTex[i].rgb * kernel[i];
      idealAlpha = max(idealAlpha, sampleTex[i].a);
  }
  
  float value = (col.r + col.g + col.b)/3.0;
  value = value * 10;

  return vec4(textColor, min(value, idealAlpha) );
}

vec4 colorImage()
{
  return texture(image,fragTex);
}

void main()
{
  if(iconState == 1)
  {
    outColor = neonImage();
  }
  else if(iconState == 2)
  {
    outColor = colorImage();
  }
}



