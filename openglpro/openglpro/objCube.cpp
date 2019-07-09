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
	// 2. �����ǵĶ������鸴�Ƶ�һ�����㻺���У���OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, verticesSize * sizeof(float), vertices, GL_STATIC_DRAW);
	// 3. �������ǵ��������鵽һ�����������У���OpenGLʹ��
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. �趨��������ָ��
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, buchang * sizeof(float), (void*)0);
	//0����location����,����vertexshader��,3����float�ĸ���,GL_FLOAT��������,GL_FALSE�Ƿ��Ǳ�׼��,5 * sizeof(float)����,(void*)0��ʼƫ����

	glEnableVertexAttribArray(0);//0��location����
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, buchang * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, buchang * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}



objCube::~objCube()
{
	delete vertices;
}
