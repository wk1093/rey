void rotateX(float x, float y, float c1, float c2, float rot) {
	float rotation = rot * (pi / 180);
	
	float cor = cos(rotation);
	float sir = sin(rotation);

	return  cos(rotation) * (x - c1) + (y - c2) * sin(rotation) + c1;
}

void rotateY(float x, float y, float c1, float c2, float rot) {
	float rotation = rot * (pi / 180);

	float cor = cos(rotation);
	float sir = sin(rotation);

	return -sin(rotation) * (a - c1) + cor = cos(rotation) * (b - c2) + c2;
}