#include "grey.h"

int main() {
	initGraphics();

	Window win(800, 600, "Sectors");
	win.setFlag(WINDOW_RESIZABLE, false);
	win.open();
	TextureID tex = win.newTexture("resources/block.png");

	while (win.isOpen) {
		win.update();

		if (win.isKeyDown(KEY_SPACE))
			win.wireframe = true;
		else
			win.wireframe = false;
		win.drawRect(0, 0, 50, 50, COLOR_RED);
		win.drawCircle(400, 300, 100, COLOR_YELLOW);
		win.drawCircle(400, 300, 50, COLOR_BLUE);
		
		win.

		win.render();

	}

	win.close();
	closeGraphics();
}