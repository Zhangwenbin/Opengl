#pragma once
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include<glm\glm\gtc\matrix_transform.hpp>
#include<glm/glm/glm.hpp>
#include<glm\glm\gtc\type_ptr.hpp>

#include"stb_image.h"

#include"Shader.h"

using namespace std;
class objBase
{
public:
	objBase();
	~objBase();
	unsigned int VAO, VBO;
	unsigned int texture1, texture2, texture3;
	float* vertices;
	int vertCount;
	unsigned int verticesSize;
	int buchang;

	const char* vs;
	const char*	fs;
	Shader shader;
	void setShader(const char*, const char*);

    void setPos(glm::vec3);
	void setScale(float s);
	virtual void initVertices();
	virtual void genVertex();
	virtual	void processTexture(const char* pic, unsigned int * ptexture, bool alpha);
	

	glm::vec3 postion;
	glm::vec3 scale;
	glm::vec4 color;
	glm::vec3 direction;

	const char*	name;

	struct Material
	{
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shiness;
	} material;


};

