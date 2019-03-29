#include "RM_Vector2D.h"

#include <math.h> 

RM_Vector2D::RM_Vector2D()
{

}

RM_Vector2D::RM_Vector2D(float eX, float eY)
{
	x = eX;
	y = eY;
}

float RM_Vector2D::speed()
{
	float magnitude = sqrt((x * x) + (y* y));
	return magnitude;
}

RM_Vector2D RM_Vector2D::perp()
{
	return RM_Vector2D(y, -x);
}
