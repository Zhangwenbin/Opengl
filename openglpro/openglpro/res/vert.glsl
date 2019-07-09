#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexcoord;
uniform mat4 model,view,projection;

uniform vec3 viewPos;

out vec3 normal;
out vec3 worldPos;

out vec3 ViewPos;
out vec2 Texcoord;

void main()
{
   gl_Position =projection*view*model*vec4(aPos.x, aPos.y, aPos.z, 1.0);
   normal=mat3(transpose(inverse( model))) * aNormal;
   worldPos=( model*vec4(aPos,1.0)).xyz;

   ViewPos=viewPos;
   Texcoord=aTexcoord;

   
};