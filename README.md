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
		// Update
		win.update();

		// Input
		if (win.isKeyPressed(KEY_F11)) {
			win.setFullscreen(!win.fullscreen);
		}
		if (win.isKeyPressed(KEY_ESCAPE)) {
			win.isOpen = false;
		}

		// Draw functions would be put here!

		// Render
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
## Draw functions
### win.drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Color color)
Draws the most primitive shape, a triangle. It takes 3 points and their x and y values and draws it with the according Color.
### win.drawRect(float x1, float y1, float width, float height, Color color, float r = 0)
Draws a rectangle with an x & y and a width & height. It also takes Color and r for rotation, which will rotate the rectangle around the middle.
### win.drawRoundedRect(float x, float y, float w1, float h1, float ro, Color color, float rot = 0)
Draws a rectangle with rounded edges. Take almost the same arguments as a rectangle, except for a float called "ro" that determines how rounded the rectangle is.
### win.drawLine(float x1, float y1, float x2, float y2, float thickness, Color color)
Draws a line that connects the two points passed in, with a thickness variable that controls the thickness of the line.
### win.drawCircle(float x, float y, float r, Color color)
Draws a circle with an x, y, a radius, and a color.
### win.drawTexture(TextureID texture, float x1, float y1, float width, float height, Color color = COLOR_WHITE, float r = 0)
Draws a texture with the passed in TextureID, x, y, width, height, and rotation. Color is automatically white, but if changed to anything else, will color the texture to that.
