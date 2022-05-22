# rey
rey is a collection of modules developed to make aspects of game development as easy as possible while still being as customizable as you want it to be. As of now, no module is 100% finished, but we're working on it as much as possible.

# grey
grey is an OpenGL based rendering engine focused on simplicity, speed, and control. It has a very simple syntax but is still powerful if you know how to use it.
## Window boilerplate

```
#include "grey.h"

int main() {
	// Init
	initGraphics();

	// Create window
	Window win(1280, 720, "grey");
	win.open();

	// Main loop
	while (win.isOpen) {
		win.update();

		win.render();
	}

	// Deinit
	win.close();
	closeGraphics();
}
```

## General functions
### initGraphics() & closeGraphics()
initGraphics should be called at the beginning before you do anything with the module. You can pass in a value that controls the amount of anti-aliasing that it should use, with 4 being the default amount if you don't pass in anything. closeGraphics should be called at the end of the program, as it frees up memory.
### Window class
The Window class can be used to create and manage a window, hosting an array of functions and variables to make your life 1000x easier. For now, the rest of this text will assume that the Window is called "win" for the sake of simplicity. The constructor takes 3 variables: the width, the height, and the title of the Window.
### win.open()
win.open simply opens the Window.
### win.close()
win.close simply closes the Window, and should be called at the end of the main loop.
### win.isOpen
win.isOpen is a boolean value that states whether or not the Window is open. This can be used to make a main loop that will run during the Window's existence by saying **while (win.isOpen)**.
### win.update()
win.update should be called at the beginning of the main loop, and it updates general variables like deltaTime and does other things like polling events.
### win.render()
win.render should be called at the end of the main loop. It'll take everything you've drawn up to this point and send it in a few batch calls.
