#include "grey.h"

int main()
{
	initGraphics();

	Window win(1280, 720, "grey");
	win.open();

	while (win.isOpen)
	{
		win.update();

		win.render();
	}

	win.close();
	closeGraphics();
}