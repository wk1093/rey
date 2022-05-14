#include "grey.h"

int main()
{
	initGraphics();

	Window win(1280, 720, "grey");
	win.open();
	win.setBackgroundColor(COLOR_WHITE);

	while (win.isOpen)
	{
		win.update();

		win.render();
	}

	win.close();
	closeGraphics();
}