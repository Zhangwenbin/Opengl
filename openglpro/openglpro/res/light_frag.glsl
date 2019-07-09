#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightColor;
void main()
{
   FragColor =vec4(lightColor,1)+mix(texture(texture1,TexCoord),texture(texture2,vec2(TexCoord.x,TexCoord.y)),0.5);
};