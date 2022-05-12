

class Shader {
private:
	GLuint shaderProgram;
public:
	Shader(const char* vertexShader, const char* fragmentShader) {
		// Vertex shader
		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShaderID, 1, &vertexShader, NULL);
		glCompileShader(vertexShaderID);
		int status; glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &status);
		if (!status) { std::cout << "Error compiling vertex shader!\n"; }
		// Fragment shader
		GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderID, 1, &fragmentShader, NULL);
		glCompileShader(fragmentShaderID);
		glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &status);
		if (!status) { std::cout << "Error compiling fragment shader!\n"; }
		// Shader program
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShaderID);
		glAttachShader(shaderProgram, fragmentShaderID);
		glLinkProgram(shaderProgram);
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
		if (!status) { std::cout << "Error compiling shader program!\n"; }
		// Clean up
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	void use() { glUseProgram(shaderProgram); }

	void setBool(const char* name, bool value) const { glUniform1i(glGetUniformLocation(shaderProgram, name), (int)value); }
	void setInt(const char* name, int value) const { glUniform1i(glGetUniformLocation(shaderProgram, name), value); }
	void setFloat(const char* name, float value) const { glUniform1f(glGetUniformLocation(shaderProgram, name), value); }
	void setFloat4(const char* name, float value[4]) const { glUniform4f(glGetUniformLocation(shaderProgram, name), value[0], value[1], value[2], value[3]); }
	void setVec2(const char* name, float x, float y) const { glUniform2f(glGetUniformLocation(shaderProgram, name), x, y); }
};