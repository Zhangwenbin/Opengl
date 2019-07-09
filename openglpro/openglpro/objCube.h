#pragma once
#include "objBase.h"

class objCube :
	public objBase
{
public:
	objCube();
	~objCube();
	objCube(glm::vec3);
	void genVertex();
	void initVertices();

};

