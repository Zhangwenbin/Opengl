#version 330 core
out vec4 FragColor;

in vec3 normal;
in vec3 worldPos;
in vec3 ViewPos;
in vec2 Texcoord;

struct Material{
   vec3 color;
   sampler2D diffuseTex;
   sampler2D specularTex;
   sampler2D emissionTex;
   float shiness;
};

struct Light{
   vec3 color;
   vec4 position;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular; 

   float constant;
   float linear;
   float quadratic;

};

uniform Material material;
uniform Light light;

//in vec3 diffColor;
//in vec3 specularColor;
void main()
{
   float ka=0.1;
   float kd=0.3;
   float ks=0.6;

   vec3 ambient=ka*light.ambient;//环境光

   vec3 lightDir;
   vec4 LightPos=light.position;
   float atten=1;

   if(LightPos.w==0){
    lightDir=normalize(-LightPos.xyz);
   }else{
    lightDir=normalize(LightPos.xyz-worldPos);
	float dis=length(LightPos.xyz-worldPos);
	 atten=1.0/(light.constant+light.linear*dis+light.quadratic*dis*dis);
   }
  
  vec3  norm=normalize(normal);
  float diff=max(dot(lightDir,norm),ambientStrenghth);
  vec3 diffColor= kd*diff*light.diffuse*texture(material.diffuseTex,Texcoord).rgb; //漫反射

  vec3 refDir=reflect(-lightDir,norm);
  vec3 viewDir=normalize( ViewPos-worldPos);
  float specular=max(dot(refDir,viewDir),0);
  vec3 specularColor=ks*pow(specular,material.shiness)*light.specular*(texture(material.specularTex,Texcoord).rgb).rgb;


   FragColor =vec4((ambient+diffColor+specularColor)*atten,1.0);//+texture(material.emissionTex,Texcoord).rgb,1.0);
};


