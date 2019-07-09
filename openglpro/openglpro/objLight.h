#pragma once
#include "objBase.h"
class objLight :
	public objBase
{
public:
	objLight();
	~objLight();
	objLight(glm::vec3);
	void initVertices();
	bool isDirection;
};

