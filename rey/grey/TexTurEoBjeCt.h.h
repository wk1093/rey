#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "texture_parametersssss.h"
typedef unsigned int TextureID;

class Texture {
public:
	GLuint VAO, VBO;
	unsigned int texture;
	std::vector<float> triangles;
	int verticeCount = 0;
	std::vector<int> shapeVerticies;
	int stack = 0;

	Texture(std::string filePath, int filter=FILTER_LINEAR) {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles.data()) * 9 * verticeCount, triangles.data(), GL_DYNAMIC_DRAW); // Maybe changes buffer data size later

		// Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// Color
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		// Texture coords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float)));
		glEnableVertexAttribArray(2);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		int width, height, nrChannels;

		unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 4);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			std::cout << "Failed to load texture at '" << filePath.c_str() << "'.\n";
		}
		stbi_image_free(data);
	}
	
	void addVertice(float verts[9]) {
		for (int i = 0; i < 9; i++) {
			triangles.push_back(verts[i]);
		}
		verticeCount++;
		stack++;
	}
	void addTriangle(float verts[27]) {
		for (int i = 0; i < 27; i++) {
			triangles.push_back(verts[i]);
		}
		verticeCount += 3;
		stack += 3;
	}

	void endShape() {
		shapeVerticies.push_back(stack);
		stack = 0;
	}

	void draw(GLenum type) {
		std::vector<int> first;
		std::vector<int> count;
		int tempInt = 0;
		for (int i = 0; i < shapeVerticies.size(); i++) {
			count.push_back(shapeVerticies[i]);
			first.push_back(tempInt);
			tempInt += shapeVerticies[i];
		}
		glMultiDrawArrays(type, first.data(), count.data(), shapeVerticies.size());
		shapeVerticies = {};
	}
	void setUpVAO() {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles.data()) * 9 * verticeCount, triangles.data(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void drawRect(float x1, float y1, float zmod, float width, float height, Color color) {
		float cR, cG, cB, cA; cR = float(color[0]) / 255; cG = float(color[1]) / 255; cB = float(color[2]) / 255; cA = float(color[3]) / 255;
		float x = x1;
		float y = y1;
		y += height;
		y -= y * 2;
		float passIn1[27] = { x, y, zmod, cR,cG,cB,cA, 0.0f, 1.0f, x, y + height, zmod, cR,cG,cB,cA, 0.0f, 0.0f, x + width, y + height, zmod, cR,cG,cB,cA, 1.0f, 0.0f };
		float passIn2[9] = { x + width, y, zmod, cR,cG,cB,cA, 1.0f, 1.0f };
		addTriangle(passIn1);
		addVertice(passIn2);
		endShape();
	}
	void flushVAO() {
		triangles = { };
		verticeCount = 0;
		stack = 0;
		shapeVerticies = { };
	}
};