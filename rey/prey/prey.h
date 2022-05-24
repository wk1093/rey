#include <iostream>

bool AABB(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) {
	if (x1 < x2 + w2 && x1 + w1 > x2 && y1 < y2 + h2 && y1 + h1 > y2) { return true; }
	return false;
}

void initPhysics() {

}

void closePhysics() {

}

typedef unsigned int PhysicsRectID;
class PhysicsRect {
public:
	std::string type = "static";
	float x = 0.0f, y = 0.0f, width = 0.0f, height = 0.0f, density = 0.0f, rotation = 0.0f;
	float velocityX = 0.0f, velocityY = 0.0f;
	PhysicsRect(std::string _type, float _x, float _y, float _width, float _height, float _density, float _rotation)
		: type(_type), x(_x), y(_y), width(_width), height(_height), density(_density), rotation(_rotation) { }
	bool isCollidingWith(PhysicsRect rect) {
		if (AABB(x, y, width, height, rect.x, rect.y, rect.width, rect.height)) { return true; }
		return false;
	}
};

class PhysicsWorld {
private:
	float gravityX = 0.0f, gravityY = 9.81f;
public:
	std::vector<PhysicsRect> rects;
	PhysicsWorld(float _gravityX, float _gravityY)
		: gravityX(_gravityX), gravityY(_gravityY) {
	}
	PhysicsRectID newRect(std::string type, float x, float y, float width, float height, float density, float rotation) {
		rects.push_back(PhysicsRect(type, x, y, width, height, density, rotation));
		return rects.size() - 1;
	}
	void update(float deltaTime) {
		for (int i = 0; i < rects.size(); i++) {
			rects[i].velocityY += (gravityY * deltaTime) * rects[i].density;
			rects[i].y += rects[i].velocityY;
		}
	}
};