#include "Key.h"
#include "Window_Flags.h"
#include "Shader.h"
#include "shaders.h"
#include "VAO.h"
#include "c.a.m.e.r.a.h"
int WIDTH, HEIGHT;

// Generally used functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	WIDTH = width; HEIGHT = height;
}

// Window class
class Window
{
private:
	GLFWwindow* windowHandle = 0;
	VAO triangleVAO;
	VAO triangleFanVAO;
	std::vector<Texture> textures;
	Shader* colorShader = 0;
	Shader* textureShader = 0;
	Color backgroundColor = { 0, 0, 0, 255 };
	bool shouldClearBackground = false;
	float deltaTime = 0.0f; float lastFrame = 0.0f;
	float currentFrame;
	float zmod = 0.0f;
	Key keys;
public:
	bool isOpen, debugInfo = false;
	int width = WIDTH; int height = HEIGHT;
	int x = 0; int y = 0;
	double mouseX = 0; double mouseY = 0;
	const char* title;
	Camera camera;

	TextureID newTexture(std::string filePath) {
		textures.push_back(Texture(filePath));
		return textures.size() - 1;
	}

	void drawRect(float x1, float y1, float width, float height, Color color, float r=0) {
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


		float passIn1[21] = { a1*cos(r1)+c1, a1*sin(r1)+c2, zmod, cR,cG,cB,cA,  a1 * cos(r2) + c1, a1 * sin(r2) + c2, zmod, cR,cG,cB,cA, a1 * cos(r3) + c1, a1 * sin(r3) + c2, zmod, cR,cG,cB,cA };
		float passIn2[7] = { a1 * cos(r4) + c1, a1 * sin(r4) + c2, zmod, cR,cG,cB,cA };
		triangleFanVAO.addTriangle(passIn1);
		triangleFanVAO.addVertice(passIn2);
		triangleFanVAO.endShape();
		zmod -= 0.000001f;
	}

	void drawTexture(TextureID texture, float x1, float y1, float width, float height, Color color=COLOR_WHITE, float r=0) {
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


		float passIn1[27] = { a1 * cos(r1) + c1, a1 * sin(r1) + c2, zmod, cR,cG,cB,cA, 0.0f, 1.0f, a1 * cos(r2) + c1, a1 * sin(r2) + c2, zmod, cR,cG,cB,cA, 0.0f, 0.0f, a1 * cos(r3) + c1, a1 * sin(r3) + c2, zmod, cR,cG,cB,cA, 1.0f, 0.0f };
		float passIn2[9] = { a1 * cos(r4) + c1, a1 * sin(r4) + c2, zmod, cR,cG,cB,cA, 1.0f, 1.0f };
		textures[texture].addTriangle(passIn1);
		textures[texture].addVertice(passIn2);
		textures[texture].endShape();
		zmod -= 0.000001f;
	}
	void drawCircle(float x, float y, float r, Color color) {
		float cR, cG, cB, cA; cR = float(color[0]) / 255; cG = float(color[1]) / 255; cB = float(color[2]) / 255; cA = float(color[3]) / 255;
		y = -y;
		float pi = 3.1415926535897932384626433;
		float pi2 = 2 * pi;
		int amount = r;
		float passIn[7] = { x, y, zmod, cR, cG, cB, cA };
		triangleFanVAO.addVertice(passIn);
		for (int i = 0; i <= amount; i++) {
			float passIn2[7] = { x + (r * cos(i * pi2 / amount)), y + (r * sin(i * pi2 / amount)), zmod, cR, cG, cB, cA };
			triangleFanVAO.addVertice(passIn2);
		}
		triangleFanVAO.endShape();
		zmod -= 0.000001f;
	}
	void drawRectGradient(float x, float y, float width, float height, Color topColor, Color bottomColor) {
		float tR, tG, tB, tA; tR = float(bottomColor[0]) / 255; tG = float(bottomColor[1]) / 255; tB = float(bottomColor[2]) / 255; tA = float(bottomColor[3]) / 255;
		float bR, bG, bB, bA; bR = float(topColor[0]) / 255; bG = float(topColor[1]) / 255; bB = float(topColor[2]) / 255; bA = float(topColor[3]) / 255;
		y += height;
		y -= y * 2;
		//triangleVAO.addTriangle(new float[21]{ x, y, 0, tR,tG,tB,tA, x, y + height, 0, bR,bG,bB,bA, x + width, y + height, 0, bR,bG,bB,bA });
		//triangleVAO.addTriangle(new float[21]{ x, y, 0, tR,tG,tB,tA, x + width, y, 0, tR,tG,tB,tA, x + width, y + height, 0, bR,bG,bB,bA });
		float passIn1[21] = { x, y, zmod, tR,tG,tB,tA, x, y + height, zmod, bR,bG,bB,bA, x + width, y + height, zmod, bR,bG,bB,bA };
		float passIn2[7] = { x + width, y, zmod, tR,tG,tB,tA };
		triangleFanVAO.addTriangle(passIn1);
		triangleFanVAO.addVertice(passIn2);
		triangleFanVAO.endShape();
		zmod -= 0.000001f;
	}
	void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Color color) {
		float cR, cG, cB, cA; cR = float(color[0]) / 255; cG = float(color[1]) / 255; cB = float(color[2]) / 255; cA = float(color[3]) / 255;
		float passIn[21] = { x1, -y1, zmod, cR,cG,cB,cA, x2, -y2, zmod, cR,cG,cB,cA, x3, -y3, zmod, cR,cG,cB,cA };
		triangleVAO.addTriangle(passIn);
		zmod -= 0.000001f;
	}
	void setFlag(uint32_t flag, bool state) {
		glfwSetWindowAttrib(windowHandle, flag, state);
	}
	Window(unsigned int w_width, unsigned int w_height, const char* _title) {
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		windowHandle = glfwCreateWindow(w_width, w_height, _title, NULL, NULL);
		x = (mode->width / 2) - (w_width / 2);
		y = (mode->height / 2) - (w_height / 2);
		glfwSetWindowPos(windowHandle, x, y);
		if (!windowHandle) { std::cout << "Window creation failure! (GLFW)\n"; glfwTerminate(); }
		WIDTH = w_width; HEIGHT = w_height;
		title = _title;
		width = w_width;
		height = w_height;
	}
	void open() {
		glfwMakeContextCurrent(windowHandle);
		glfwSetFramebufferSizeCallback(windowHandle, framebuffer_size_callback);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { std::cout << "Graphics init failure! (glad)\n"; }
		isOpen = true;
		colorShader = new Shader(colorVertexShader.c_str(), colorFragmentShader.c_str());
		textureShader = new Shader(textureVertexShader.c_str(), textureFragmentShader.c_str());
		triangleVAO.initVAO();
		triangleFanVAO.initVAO();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void close() {
		isOpen = false;
		glfwSetWindowShouldClose(windowHandle, true);
		delete colorShader;
		delete textureShader;
	}

	bool isKeyPressed(int key) {
		return keys.FindTempKey(key);
	}
	bool isKeyDown(int key) {
		return keys.FindKey(key);
	}

	bool isMousePressed(int button) {
		return (glfwGetMouseButton(windowHandle, button) == GLFW_PRESS);
	}

	void clearScreen(Color color) {
		glClearColor(float(color[0]) / 255, float(color[1]) / 255, float(color[2]) / 255, float(color[3]) / 255);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void setBackgroundColor(Color color) {
		shouldClearBackground = true;
		for (int i = 0; i < 3; i++) {
			backgroundColor[i] = color[i];
		}
	}
	void update() {
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		isOpen = !glfwWindowShouldClose(windowHandle);
		width = WIDTH; height = HEIGHT;
		glfwGetWindowPos(windowHandle, &x, &y);
		glfwGetCursorPos(windowHandle, &mouseX, &mouseY);
		glfwPollEvents();
		keys.UpdateKeys(windowHandle);
	}
	void render() {
		glClearColor(float(backgroundColor[0]) / 255, float(backgroundColor[1]) / 255, float(backgroundColor[2]) / 255, float(backgroundColor[3]) / 255);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		triangleVAO.setUpVAO();
		triangleFanVAO.setUpVAO();
		for (int i = 0; i < textures.size(); i++) {
			textures[i].setUpVAO();
		}

		colorShader->use();
		colorShader->setVec2("viewport", WIDTH/2, HEIGHT/2);
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

		if (debugInfo) {
			float afterRenderTime = glfwGetTime() - currentFrame;
			int debugVerticeCount = triangleVAO.verticeCount + triangleFanVAO.verticeCount;
			for (int i = 0; i < textures.size(); i++) {
				debugVerticeCount += textures[i].verticeCount;
			}
			std::cout << "\nVertice count: " << debugVerticeCount;
			std::cout << "\nTotal time spent rendering: " << afterRenderTime*1000 << " milliseconds";
			std::cout << "\nFPS: " << 1 / afterRenderTime;
			std::cout << "\nTotal application time: " << glfwGetTime() << " seconds";
			std::cout << "\n=====================";
		}

		triangleVAO.flushVAO();
		triangleFanVAO.flushVAO();
		for (int i = 0; i < textures.size(); i++) {
			textures[i].flushVAO();
		}
		glfwSwapBuffers(windowHandle);

		zmod = 0.0f;
	}

	// Returns the time since the last frame was drawn. Multiply frame-dependent variables by this value to make them frame independent.
	float getDeltaTime() { return deltaTime; }
	// Sets the mouse position relative to the window's position
	void setMousePosition(int x, int y) { glfwSetCursorPos(windowHandle, x, y); mouseX = x; mouseY = y; }
	// Sets the position of the window
	void setWindowPosition(int _x, int _y) { glfwSetWindowPos(windowHandle, _x, _y); x = _x; y = _y; }
	// Sets the dimensions of the window
	void setWindowDimensions(int _width, int _height) { glfwSetWindowSize(windowHandle, _width, _height); width = _width; height = _height; }
	// Sets the title of the window
	void setWindowTitle(std::string _title) { glfwSetWindowTitle(windowHandle, _title.c_str()); title = _title.c_str(); }
};