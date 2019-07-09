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

struct dirLight{
   vec3 color;
   vec4 position;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular; 

};

struct pointLight{
   vec3 color;
   vec4 position;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular; 

   float constant;
   float linear;
   float quadratic;

};

struct sportLight{
   vec3 color;
   vec4 position;
   vec3 direction;
   float cutoff;
   float outcutoff;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular; 
};

uniform Material material;
uniform dirLight dirlight;
uniform pointLight poilight[4];
uniform sportLight spolight;

 vec3 calcDirLight(dirLight ,vec3 ,vec3 );
 vec3 calcPointLight(pointLight ,vec3 ,vec3,vec3);
 vec3 calcSportLight(sportLight ,vec3 ,vec3,vec3);

void main()
{

   vec3 viewDir=normalize( ViewPos-worldPos);
   vec3 dirColor=calcDirLight(dirlight,normal,viewDir);
   vec3 pointColor=vec3(0);
   for(int i=0;i<4;i++)
   pointColor+=calcPointLight(poilight[i],normal,viewDir,worldPos);
   vec3 sportColor=calcSportLight(spolight,normal,viewDir,worldPos);
   FragColor =vec4((dirColor+pointColor+sportColor),1.0);//+texture(material.emissionTex,Texcoord).rgb,1.0);
};

vec3 calcDirLight(dirLight light,vec3 normal,vec3 viewDir ){

   float ka=0.1;
   float kd=0.5;
   float ks=0.5;

   vec3 lightDir=normalize(-light.position.xyz);
  vec3  norm=normalize(normal);
  float diff=max(dot(lightDir,norm),0);
  vec3 diffColor= kd*diff*light.diffuse*texture(material.diffuseTex,Texcoord).rgb; //Âþ·´Éä

  vec3 refDir=reflect(-lightDir,norm);
  float specular=max(dot(refDir,viewDir),0);
  vec3 specularColor=ks*pow(specular,material.shiness)*light.specular*(texture(material.specularTex,Texcoord).rgb).rgb;
  return diffColor+specularColor;
};

vec3 calcPointLight(pointLight light,vec3 normal,vec3 viewDir,vec3 fragpos ){
   float ka=0.1;
   float kd=1;
   float ks=1;

   vec3 lightDir=normalize(light.position.xyz-fragpos);
  float dis=length(light.position.xyz-fragpos);
  float atten=1.0/(light.constant+light.linear*dis+light.quadratic*dis*dis);

  vec3  norm=normalize(normal);
  float diff=max(dot(lightDir,norm),0);
  vec3 diffColor= kd*diff*light.diffuse*texture(material.diffuseTex,Texcoord).rgb*atten; //Âþ·´Éä

  vec3 refDir=reflect(-lightDir,norm);
  float specular=max(dot(refDir,viewDir),0);
  vec3 specularColor=ks*pow(specular,material.shiness)*light.specular*(texture(material.specularTex,Texcoord).rgb).rgb*atten;
  return diffColor+specularColor;
};

vec3 calcSportLight(sportLight light,vec3 normal,vec3 viewDir,vec3 fragpos ){
   float ka=0.1;
   float kd=2;
   float ks=2;

   vec3 lightDir=normalize(light.position.xyz-fragpos);
   float theta=light.cutoff-light.outcutoff;
   float epxsion=clamp((dot(-lightDir,normalize(light.direction))-light.outcutoff)/theta,0,1);

  vec3  norm=normalize(normal);
  float diff=max(dot(lightDir,norm),0);
  vec3 diffColor= kd*diff*light.diffuse*texture(material.diffuseTex,Texcoord).rgb*epxsion; //Âþ·´Éä

  vec3 refDir=reflect(-lightDir,norm);
  float specular=max(dot(refDir,viewDir),0);
  vec3 specularColor=ks*pow(specular,material.shiness)*light.specular*(texture(material.specularTex,Texcoord).rgb).rgb*epxsion;
  return diffColor+specularColor;
};

