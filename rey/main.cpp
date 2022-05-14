#include "grey.h"

int main()
{
	initGraphics();

	Window win(1280, 720, "grey");
	win.open();
	win.setBackgroundColor(COLOR_WHITE);

	float rot = 0;
	TextureID texture = win.newTexture("resources/block.png");

	while (win.isOpen)
	{
		win.update();
		rot += .5f;
		if (rot == 360)
			rot = 0;

		win.drawTexture(texture, 1280/2, 720/2, 200, 100, COLOR_WHITE, rot);
		win.render();
	}

	win.close();
	closeGraphics();
}