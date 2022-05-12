class VAO {
public:
	GLuint VAO, VBO;
	std::vector<float> triangles;
	int verticeCount = 0;
	std::vector<int> shapeVerticies;
	int stack = 0;
	void addVertice(float verts[7]) {
		for (int i = 0; i < 7; i++) {
			triangles.push_back(verts[i]);
		}
		verticeCount++;
		stack++;
	}
	void addTriangle(float verts[21]) {
		for (int i = 0; i < 21; i++) {
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
		glBindVertexArray(VAO);
		glMultiDrawArrays(type, first.data(), count.data(), shapeVerticies.size());
		shapeVerticies = {};
	}

	void initVAO() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles.data()) * 7 * verticeCount, triangles.data(), GL_DYNAMIC_DRAW);

		// Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// Color
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	void setUpVAO() {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(triangles.data()) * 7 * verticeCount, triangles.data(), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void flushVAO() {
		triangles = { };
		verticeCount = 0;
		stack = 0;
		shapeVerticies = { };
	}
};