#include "objTriangle.h"



objTriangle::objTriangle()
{
	vertCount = 3;
	
	vertices = new float[15] 
	{
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f 
	};
	verticesSize = 15;
	buchang = 5;

}


objTriangle::~objTriangle()
{
	delete vertices;
}
