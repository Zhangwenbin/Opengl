#include "objCube.h"

objCube::objCube()
{
	initVertices();
}

objCube::objCube(glm::vec3 pos) {
	setPos(pos);
	initVertices();
}


void objCube:: initVertices() {
	vertCount = 36;
	vertices = new float[288]
	{
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,0,0,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,1,0,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,1,1,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,1,1,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,0,1,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,0,0,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,0,0,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,1,0,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,1,1,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,01,1,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,0,01,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,0,0,

	 -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};
	verticesSize = 288;
	buchang = 8;
}

void objCube::genVertex() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// 2. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(float), vertices, GL_STATIC_DRAW);
	// 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. 设定顶点属性指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, buchang * sizeof(float), (void*)0);
	//0代表location索引,用于vertexshader中,3代表float的个数,GL_FLOAT参数类型,GL_FALSE是否是标准化,5 * sizeof(float)步长,(void*)0起始偏移量

	glEnableVertexAttribArray(0);//0是location索引
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, buchang * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, buchang * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}



objCube::~objCube()
{
	delete vertices;
}
