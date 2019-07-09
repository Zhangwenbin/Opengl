#pragma once
#include "objLight.h"
class objSportLight :
	public objLight
{
public:
	objSportLight();
	~objSportLight();
	float cutoff;
	float outCutOff;
};

