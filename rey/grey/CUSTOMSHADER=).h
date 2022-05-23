typedef unsigned int ShaderID;

struct CustomShaderVS {
	std::string colorVertexShader;
	std::string colorFragmentShader;
	std::string textureVertexShader;
	std::string textureFragmentShader;
};

class CustomShader {
private:
	VAO triangleVAO;
	VAO triangleFanVAO;
	Shader* colorShader;
	Shader* textureShader;
public:
	std::vector<Texture> textures;
	TextureID newTexture(std::string filePath, int filter = FILTER_LINEAR) {
		textures.push_back(Texture(filePath, filter));
		return textures.size() - 1;
	}

	CustomShader(const char* colorVertexShader, const char* colorFragmentShader, const char* textureVertexShader, const char* textureFragmentShader) {
		colorShader = new Shader(colorVertexShader, colorFragmentShader);
		textureShader = new Shader(textureVertexShader, textureFragmentShader);
		triangleVAO.initVAO();
		triangleFanVAO.initVAO();
	}
	CustomShader(CustomShaderVS customShaderVS) {
		CustomShader(customShaderVS.colorVertexShader.c_str(), customShaderVS.colorFragmentShader.c_str(), customShaderVS.textureVertexShader.c_str(), customShaderVS.textureFragmentShader.c_str());
	}
	~CustomShader() {
		delete colorShader;
		delete textureShader;
	}
	void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Color color, float zmod) {
		float cR, cG, cB, cA; cR = float(color[0]) / 255; cG = float(color[1]) / 255; cB = float(color[2]) / 255; cA = float(color[3]) / 255;
		float passIn[21] = { x1, -y1, zmod, cR,cG,cB,cA, x2, -y2, zmod, cR,cG,cB,cA, x3, -y3, zmod, cR,cG,cB,cA };
		triangleVAO.addTriangle(passIn);
	}
	void drawRect(float x1, float y1, float width, float height, Color color, float zmod, float r = 0) {
		float cR, cG, cB, cA; cR = float(color[0]) / 255; cG = float(color[1]) / 255; cB = float(color[2]) / 255; cA = float(color[3]) / 255;
		float x = x1;
		float y = y1;
		y += height;
		y -= y * 2;
		float pi = 3.1415926535897932384626433;
		float rotation = r * (pi / 180);
		float a1 = sqrt(pow((width / 2), 2) + pow((height / 2), 2));
		float r0 = asin(((height / 2) * (sin(pi / 2))) / (a1));
		float r1 = r0 + rotation;
		float r2 = -r0 + rotation;
		float r3 = r1 - pi;
		float r4 = r2 - pi;
		float c1 = x + width / 2;
		float c2 = y + height / 2;
		float passIn1[21] = { a1 * cos(r1) + c1, a1 * sin(r1) + c2, zmod, cR,cG,cB,cA,  a1 * cos(r2) + c1, a1 * sin(r2) + c2, zmod, cR,cG,cB,cA, a1 * cos(r3) + c1, a1 * sin(r3) + c2, zmod, cR,cG,cB,cA };
		float passIn2[7] = { a1 * cos(r4) + c1, a1 * sin(r4) + c2, zmod, cR,cG,cB,cA };
		triangleFanVAO.addTriangle(passIn1);
		triangleFanVAO.addVertice(passIn2);
		triangleFanVAO.endShape();
	}
	void drawRoundedRect(float x, float y, float w1, float h1, float ro, Color color, float zmod, float rot = 0)
	{
		float cR, cG, cB, cA; cR = float(color[0]) / 255; cG = float(color[1]) / 255; cB = float(color[2]) / 255; cA = float(color[3]) / 255;
		float x1 = x;
		float y1 = y;
		y1 += h1;
		y1 -= y1 * 2;
		float pi = 3.1415926535897932384626433;
		float rotation = rot * (pi / 180);
		float c1 = x1 + w1 / 2;
		float c2 = y1 + h1 / 2;

		auto trax = [c1, c2, rotation](float a, float b) -> float
		{
			return  rotateX(a, b, c1, c2, rotation);
		};
		auto tray = [c1, c2, rotation](float a, float b) -> float
		{
			return rotateY(a, b, c1, c2, rotation);
		};

		auto trect = [&](float a, float b, float c, float d)
		{
			float passIn0[21] = { trax(a,b),tray(a,b),zmod,cR,cG,cB,cA, trax(a,d),tray(a,d),zmod,cR,cG,cB,cA, trax(c,d),tray(c,d),zmod,cR,cG,cB,cA };
			float passIn1[7] = { trax(c,b),tray(c,b),zmod,cR,cG,cB,cA };
			triangleFanVAO.addTriangle(passIn0); triangleFanVAO.addVertice(passIn1);
			triangleFanVAO.endShape();
		};

		auto tcircle = [&](float xii, float yii, float ri)
		{
			float xi = trax(xii, yii);
			float yi = tray(xii, yii);

			float pi = 3.1415926535897932384626433f;
			float pi2 = 2 * pi;
			int amount = ri;
			float passIn[7] = { xi, yi, zmod, cR, cG, cB, cA };
			triangleFanVAO.addVertice(passIn);
			for (int i = 0; i <= amount; i++) {
				float passIn2[7] = { xi + (ri * cos(i * pi2 / amount)), yi + (ri * sin(i * pi2 / amount)), zmod, cR, cG, cB, cA };
				triangleFanVAO.addVertice(passIn2);
			}
			triangleFanVAO.endShape();
		};


		trect(x1 + ro, y1, x1 + w1 - ro, y1 + h1);
		trect(x1, y1 + ro, x1 + w1, y1 + h1 - ro);

		tcircle(x1 + ro, y1 + ro, ro);
		tcircle(x1 + w1 - ro, y1 + ro, ro);
		tcircle(x1 + w1 - ro, y1 + h1 - ro, ro);
		tcircle(x1 + ro, y1 + h1 - ro, ro);
	}
	void drawLine(float x1, float y1, float x2, float y2, float thickness, Color color, float zmod) {
		float cR, cG, cB, cA; cR = float(color[0]) / 255; cG = float(color[1]) / 255; cB = float(color[2]) / 255; cA = float(color[3]) / 255;
		y1 -= y1 * 2;
		y2 -= y2 * 2;
		float passIn1[21] = { x1 - (thickness / 2), y1 - (thickness / 2), zmod, cR, cG, cB, cA, x1 - (thickness / 2), y1 + (thickness / 2), zmod, cR, cG, cB, cA, x2 + (thickness / 2), y2 + (thickness / 2), zmod, cR, cG, cB, cA };
		float passIn2[7] = { x2 + (thickness / 2), y2 - (thickness / 2), zmod, cR, cG, cB, cA };
		triangleFanVAO.addTriangle(passIn1);
		triangleFanVAO.addVertice(passIn2);
		triangleFanVAO.endShape();
	}
	void drawCircle(float x, float y, float r, Color color, float zmod) {
		float cR, cG, cB, cA; cR = float(color[0]) / 255; cG = float(color[1]) / 255; cB = float(color[2]) / 255; cA = float(color[3]) / 255;
		y = -y;
		float pi = 3.1415926535897932384626433f;
		float pi2 = 2 * pi;
		int amount = r;
		float passIn[7] = { x, y, zmod, cR, cG, cB, cA };
		triangleFanVAO.addVertice(passIn);
		for (int i = 0; i <= amount; i++) {
			float passIn2[7] = { x + (r * cos(i * pi2 / amount)), y + (r * sin(i * pi2 / amount)), zmod, cR, cG, cB, cA };
			triangleFanVAO.addVertice(passIn2);
		}
		triangleFanVAO.endShape();
	}
	void drawSector(float x, float y, float r, float degree, Color color, float zmod, float rot = 0, float accuracy = 10) {
		float cR, cG, cB, cA; cR = float(color[0]) / 255; cG = float(color[1]) / 255; cB = float(color[2]) / 255; cA = float(color[3]) / 255;
		y = -y;
		float pi = 3.1415926535897932384626433f;
		float pi2 = 2 * pi;
		float rotation = rot * (pi / 180);
		int amount = accuracy * r;
		float passIn[7] = { x, y, zmod, cR, cG, cB, cA };
		triangleFanVAO.addVertice(passIn);
		for (int i = 0; i <= amount * ((degree) / 360); i++) {
			float passIn2[7] = { x + (r * cos(i * pi2 / amount + rotation)), y + (r * sin(i * pi2 / amount + rotation)), zmod, cR, cG, cB, cA };
			triangleFanVAO.addVertice(passIn2);
		}
		triangleFanVAO.endShape();
	}
	void drawTexture(TextureID texture, float x1, float y1, float width, float height, float zmod, Color color = COLOR_WHITE, float r = 0) {
		float cR, cG, cB, cA; cR = float(color[0]) / 255; cG = float(color[1]) / 255; cB = float(color[2]) / 255; cA = float(color[3]) / 255;
		float x = x1;
		float y = y1;
		y += height;
		y -= y * 2;
		float pi = 3.1415926535897932384626433f;
		float rotation = r * (pi / 180);
		float a1 = sqrt(pow((width / 2), 2) + pow((height / 2), 2));
		float r0 = asin(((height / 2) * (sin(pi / 2))) / (a1));
		float r1 = r0 + rotation;
		float r2 = -r0 + rotation;
		float r3 = r1 - pi;
		float r4 = r2 - pi;
		float c1 = x + width / 2;
		float c2 = y + height / 2;
		float passIn1[27] = { a1 * cos(r1) + c1, a1 * sin(r1) + c2, zmod, cR,cG,cB,cA, 0.0f, 1.0f, a1 * cos(r2) + c1, a1 * sin(r2) + c2, zmod, cR,cG,cB,cA, 0.0f, 0.0f, a1 * cos(r3) + c1, a1 * sin(r3) + c2, zmod, cR,cG,cB,cA, 1.0f, 0.0f };
		float passIn2[9] = { a1 * cos(r4) + c1, a1 * sin(r4) + c2, zmod, cR,cG,cB,cA, 1.0f, 1.0f };
		textures[texture].addTriangle(passIn1);
		textures[texture].addVertice(passIn2);
		textures[texture].endShape();
	}

	void draw(Camera camera, float WIDTH, float HEIGHT) {
		triangleVAO.setUpVAO();
		triangleFanVAO.setUpVAO();
		for (int i = 0; i < textures.size(); i++) {
			textures[i].setUpVAO();
		}

		colorShader->use();
		colorShader->setVec2("viewport", WIDTH / 2, HEIGHT / 2);
		colorShader->setVec3("offset", camera.x, camera.y, camera.z);

		// Draw triangles 
		glBindVertexArray(triangleVAO.VAO);
		glDrawArrays(GL_TRIANGLES, 0, triangleVAO.verticeCount);

		// Draw triangle fans
		glBindVertexArray(triangleFanVAO.VAO);

		triangleFanVAO.draw(GL_TRIANGLE_FAN);

		if (textures.size() > 0) {
			textureShader->use();
			textureShader->setVec2("viewport", WIDTH / 2, HEIGHT / 2);
			textureShader->setVec3("offset", camera.x, camera.y, camera.z);
		}

		// Draw textures
		for (int i = 0; i < textures.size(); i++) {
			glBindTexture(GL_TEXTURE_2D, textures[i].texture);
			glBindVertexArray(textures[i].VAO);
			textures[i].draw(GL_TRIANGLE_FAN);
		}

		triangleVAO.flushVAO();
		triangleFanVAO.flushVAO();
		for (int i = 0; i < textures.size(); i++) {
			textures[i].flushVAO();
		}
	}
};