class Triangle {
private:
	unsigned int ID = NULL;
public:
	float points[9];
	Triangle(float point1x, float point1y, float point1z, float point2x, float point2y, float point2z, float point3x, float point3y, float point3z)
	: points{ point1x, point1y, point1z, point2x, point2y, point2z, point3x, point3y, point3z } { }
};

class Rectangle {
private:
	unsigned int ID = NULL;
public:
	float points1[9];
	float points2[9];
	float x, y, w, h;
	Rectangle(float x, float y, float w, float h)
	: points1{ x, y, 0, x, y+h, 0, x+w, y+h, 0 }, points2{ x, y, 0, x+w, y, 0, x+w, y+h, 0 }, x(x), y(y), w(w), h(h) { }
};