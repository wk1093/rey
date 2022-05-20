#include "Key.h"
#include "Window_Flags.h"
#include "Shader.h"
#include "shaders.h"
#include "VAO.h"
#include "c.a.m.e.r.a.h"
#include "mrey.h"
#include "CUSTOMSHADER=).h"

// Generally used functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Window class
class Window
{
private:
	GLFWwindow* windowHandle = 0;
	std::vector<CustomShader*> shaders;
	Color backgroundColor = { 0, 0, 0, 255 };
	bool shouldClearBackground = false;
	float deltaTime = 0.0f; float lastFrame = 0.0f;
	float currentFrame;
	float zmod = 0.0f;
	Key keys;
	float prevX = 0.0f, prevY = 0.0f, prevWidth = 0.0f, prevHeight = 0.0f;
	unsigned int currentShader = 0;
	// Why do you make me do this manually glfw?
	GLFWmonitor* getWindowMonitor() {
		int count;
		GLFWmonitor** monitors = glfwGetMonitors(&count);
		std::vector<int> widths;
		for (int i = 0; i < count; i++) {
			if (i == 0) { widths.push_back(0); }
			else {
				const GLFWvidmode* modee = glfwGetVideoMode(monitors[i]);
				widths.push_back(modee->width + widths[widths.size() - 1]);
			}
		}
		for (int i = 0; i < widths.size(); i++) {
			if (i + 2 > widths.size() || x > widths[i] && x < widths[i + 1]) {
				return monitors[i];
			}
		}
	}
public:
	bool wireframe = false;
	bool isOpen, debugInfo = false;
	int width; int height;
	int x = 0; int y = 0;
	double mouseX = 0; double mouseY = 0;
	const char* title;
	Camera camera;
	bool fullscreen = false;

	ShaderID newShader(const char* colorVertexShader, const char* colorFragmentShader, const char* textureVertexShader, const char* textureFragmentShader) {
		shaders.push_back(new CustomShader(colorVertexShader, colorFragmentShader, textureVertexShader, textureFragmentShader));
		return shaders.size() - 1;
	}

	void useShader(ShaderID shader) {
		currentShader = shader;
	}
	void useDefaultShader() {
		currentShader = 0;
	}

	TextureID newTexture(std::string filePath, int filter = FILTER_LINEAR) {
		for (int i = 0; i < shaders.size(); i++) {
			shaders[i]->newTexture(filePath, filter);
		}
		return shaders[currentShader]->textures.size() - 1;
	}
	void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Color color) { shaders[currentShader]->drawTriangle(x1, y1, x2, y2, x3, y3, color, zmod); zmod -= 0.000001f; }
	void drawRect(float x1, float y1, float width, float height, Color color, float r = 0) { shaders[currentShader]->drawRect(x1, y1, width, height, color, zmod, r); zmod -= 0.000001f; }
	void drawRoundedRect(float x, float y, float w1, float h1, float ro, Color color, float rot = 0) { shaders[currentShader]->drawRoundedRect(x, y, w1, h1, ro, color, zmod, rot); zmod -= 0.000001f; }
	void drawLine(float x1, float y1, float x2, float y2, float thickness, Color color) { shaders[currentShader]->drawLine(x1, y1, x2, y2, thickness, color, zmod); zmod -= 0.000001f; }
	void drawCircle(float x, float y, float r, Color color) { shaders[currentShader]->drawCircle(x, y, r, color, zmod); zmod -= 0.000001f; }
	void drawSector(float x, float y, float r, float degree, Color color, float rot = 0, float accuracy = 10) { shaders[currentShader]->drawSector(x, y, r, degree, color, zmod, rot, accuracy); zmod -= 0.000001f; }
	void drawTexture(TextureID texture, float x1, float y1, float width, float height, Color color = COLOR_WHITE, float r = 0) { shaders[currentShader]->drawTexture(texture, x1, y1, width, height, zmod, color, r); zmod -= 0.000001f; }

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
		width = w_width; height = w_height;
		title = _title;
	}
	void open() {
		glfwMakeContextCurrent(windowHandle);
		glfwSetFramebufferSizeCallback(windowHandle, framebuffer_size_callback);
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) { std::cout << "Graphics init failure! (glad)\n"; }
		isOpen = true;
		shaders.push_back(new CustomShader(colorVertexShader.c_str(), colorFragmentShader.c_str(), textureVertexShader.c_str(), textureFragmentShader.c_str()));
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void close() {
		isOpen = false;
		glfwSetWindowShouldClose(windowHandle, true);
		glfwDestroyWindow(windowHandle);
		for (int i = 0; i < shaders.size(); i++) {
			delete shaders[i];
		}
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
		glfwGetWindowSize(windowHandle, &width, &height);
		glfwGetWindowPos(windowHandle, &x, &y);
		glfwGetCursorPos(windowHandle, &mouseX, &mouseY);
		glfwPollEvents();
		keys.UpdateKeys(windowHandle);
		if (deltaTime > 0.05f) { deltaTime = 0; }
	}
	void render() {
		if (wireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		glClearColor(float(backgroundColor[0]) / 255, float(backgroundColor[1]) / 255, float(backgroundColor[2]) / 255, float(backgroundColor[3]) / 255);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < shaders.size(); i++) {
			shaders[i]->draw(camera, width, height);
		}

		glfwSwapBuffers(windowHandle);

		zmod = 0.0f;
		currentShader = 0;
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

	void setFullscreen(bool _fullscreen)
	{
		if (fullscreen == _fullscreen) { return; }
		if (_fullscreen) {
			prevX = x;
			prevY = y;
			prevWidth = width;
			prevHeight = height;
			GLFWmonitor* currentMonitor = getWindowMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode(currentMonitor);
			glfwSetWindowMonitor(windowHandle, currentMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
			fullscreen = true;
		}
		else {
			const GLFWvidmode* mode = glfwGetVideoMode(getWindowMonitor());
			glfwSetWindowMonitor(windowHandle, NULL, prevX, prevY, prevWidth, prevHeight, mode->refreshRate);
			fullscreen = false;
		}
	}
};