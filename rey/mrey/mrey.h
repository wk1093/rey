#include <math.h>

double rotateX(float x, float y, float c1, float c2, float rot) {
	float pi = 3.1415926535897932384626433;
	float rotation = rot * (pi / 180);
	
	float cor = cos(rotation);
	float sir = sin(rotation);

	return cos(rotation) * (x - c1) + (y - c2) * sin(rotation) + c1;
}

double rotateY(float x, float y, float c1, float c2, float rot) {
	float pi = 3.1415926535897932384626433;
	float rotation = rot * (pi / 180);

	float cor = cos(rotation);
	float sir = sin(rotation);

	return -sin(rotation) * (a - c1) + cor = cos(rotation) * (b - c2) + c2;
}