#pragma once
#ifndef GLBINDTOOL_H
#define GLINDTOOL_H
#include<iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include"stb_image.h"

#include"objBase.h"

class glBindTool
{
public:
	void processVert(objBase*, unsigned int & VAO, unsigned int & VBO);
	void processTexture(const char*, unsigned int *,bool);
	 glBindTool() ;
	~glBindTool();

private:

};


void glBindTool::processVert(objBase* obj,unsigned int & VAO, unsigned int & VBO) {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// 2. �����ǵĶ������鸴�Ƶ�һ�����㻺���У���OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, obj->verticesSize * sizeof(float), obj->vertices, GL_STATIC_DRAW);
	// 3. �������ǵ��������鵽һ�����������У���OpenGLʹ��
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. �趨��������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, obj->buchang * sizeof(float), (void*)0);
	//0����location����,����vertexshader��,3����float�ĸ���,GL_FLOAT��������,GL_FALSE�Ƿ��Ǳ�׼��,5 * sizeof(float)����,(void*)0��ʼƫ����

	glEnableVertexAttribArray(0);//0��location����
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, obj->buchang * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void glBindTool::processTexture(const char* pic, unsigned int * ptexture,bool alpha) {
	// load and create a texture 
	// -------------------------

	glGenTextures(1, ptexture);
	glBindTexture(GL_TEXTURE_2D, *ptexture);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
											// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	unsigned char *data = stbi_load(pic, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0,alpha?GL_RGBA:GL_RGB, width, height, 0, alpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

inline glBindTool::glBindTool()
{
}

inline glBindTool::~glBindTool()
{
}


#endif // !GLBINDTOOL_H
