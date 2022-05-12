#include "grey.h"

int main() {
	initGraphics();
	Window win(200, 400, "TestApp");
	win.open();
	win.setBackgroundColor(COLOR_WHITE);

	while (win.isOpen) {
		win.update();

		win.render();
	}

	win.close();
	close();
}