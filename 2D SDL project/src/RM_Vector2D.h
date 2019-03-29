#pragma once

#ifndef aVector2dFILE
#define aVector2dFILE

#include <math.h> 

class RM_Vector2D
{
public:
	RM_Vector2D();
	RM_Vector2D(float eX, float eY);

	float speed();
	RM_Vector2D perp();

	float x;
	float y;
};




#endif // !aVector2dFILE

