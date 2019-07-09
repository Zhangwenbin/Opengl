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
	// 2. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, obj->verticesSize * sizeof(float), obj->vertices, GL_STATIC_DRAW);
	// 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. 设定顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, obj->buchang * sizeof(float), (void*)0);
	//0代表location索引,用于vertexshader中,3代表float的个数,GL_FLOAT参数类型,GL_FALSE是否是标准化,5 * sizeof(float)步长,(void*)0起始偏移量

	glEnableVertexAttribArray(0);//0是location索引
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
