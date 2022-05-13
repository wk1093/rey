class Timer {
	float time = 0.0f;
	bool started = false;
public:
	void start() {
		started = true;
		time = glfwGetTime();
	}
	void stop() {
		time = 0.0f;
		started = false;
	}
	// Returns the time passed (in seconds) since the timer has started
	float getTime() {
		if (started) {
			return glfwGetTime() - time;
		}
		return 0.0f;
	}
	float setTime(float _time) {
		time = _time + glfwGetTime();
	}
	bool hasStarted() {
		return started;
	}
	void restart() {
		time = 0.0f;
	}
};