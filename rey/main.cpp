#include "grey.h"

int main() {
	initGraphics();

	Window win(800, 600, "grey");
	win.setFlag(WINDOW_RESIZABLE, false);
	win.open();
	win.setBackgroundColor(COLOR_WHITE);

	while (win.isOpen) {
		win.update();

		if (win.isKeyDown(KEY_SPACE))
			win.wireframe = true;
		else
			win.wireframe = false;
		if (win.isKeyPressed(KEY_F11))
			win.setFullscreen(!win.fullscreen);
		if (win.isKeyPressed(KEY_ESCAPE))
			win.isOpen = false;

		win.drawRect(50, 50, 100, 100, COLOR_SOFT_ORANGE);
		win.drawCircle(250, 100, 50, COLOR_SOFT_ORANGE);
		win.drawRoundedRect(350, 50, 100, 100, 25.0f, COLOR_SOFT_ORANGE);

		win.render();
	}

	win.close();
	closeGraphics();
}