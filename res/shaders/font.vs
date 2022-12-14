#version 330

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 tex;

out vec2 fragTex;

uniform vec2 size;
uniform vec2 offset;
uniform vec2 position;
uniform vec2 shift;
uniform float scale;
uniform mat4 ortho;

void main()
{
   fragTex = vec2(tex);

   vec2 objPos = vec2(pos)*size + shift + offset;
   //since (* size) shrinks from center [_._] to _[.]_  we need to adjust pos to [.]__
   objPos = objPos - (vec2(1,2) - vec2(1,2)*size)/2; // here 1 and 2 are width and height in mesh
    
   vec2 worldPos = objPos*scale + position;
   gl_Position = ortho*vec4(worldPos, 0.0f, 1.0f);
}
