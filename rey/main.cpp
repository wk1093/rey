#include "grey.h"
#include <random>
#include <sstream>
#include <math.h>

int LINE_BLOCK[20] = {
	// 4 blocks (on a 0-3 grid)
	0, 1,
	1, 1,
	2, 1,
	3, 1,
	// Color
	0, 200, 200, 255,
	// Rotation rules
	-1, 1, // rot=0
	0, -1, // rot=1
	0, 0, // rot=2
	1, 0  // rot=3
};
int J_BLOCK[20] = {
	// 4 blocks (on a 0-3 grid)
	2, 0,
	2, 1,
	2, 2,
	1, 2,
	// Color
	0, 0, 200, 255,
	// Rotation rules
	0, 1, // rot=0
	-1, 0, // rot=1
	0, -1, // rot=2
	1, 0  // rot=3
};
int L_BLOCK[20] = {
	// 4 blocks (on a 0-3 grid)
	0, 0,
	0, 1,
	0, 2,
	1, 2,
	// Color
	200, 100, 0, 255,
	// Rotation rules
	0, 1, // rot=0
	-1, 0, // rot=1
	0, -1, // rot=2
	1, 0  // rot=3
};
int SQUARE_BLOCK[20] = {
	// 4 blocks (on a 0-3 grid)
	0, 0,
	1, 0,
	0, 1,
	1, 1,
	// Color
	200, 200, 0, 255,
	// Rotation rules
	0, 2, // rot=0
	-2, 0, // rot=1
	0, -2, // rot=2
	2, 0  // rot=3
};
int S_BLOCK[20] = {
	// 4 blocks (on a 0-3 grid)
	1, 0,
	2, 0,
	0, 1,
	1, 1,
	// Color
	0, 200, 0, 255,
	// Rotation rules
	-1, 2, // rot=0
	-1, -1, // rot=1
	0, -1, // rot=2
	2, 0  // rot=3
};
int T_BLOCK[20] = {
	// 4 blocks (on a 0-3 grid)
	1, 0,
	0, 1,
	1, 1,
	2, 1,
	// Color
	100, 0, 200, 255,
	// Rotation rules
	0, 1, // rot=0
	-1, 0, // rot=1
	0, -1, // rot=2
	1, 0  // rot=3
};
int Z_BLOCK[20] = {
	// 4 blocks (on a 0-3 grid)
	0, 0,
	1, 0,
	1, 1,
	2, 1,
	// Color
	200, 0, 0, 255,
	// Rotation rules
	-1, 2, // rot=0
	-1, -1, // rot=1
	0, -1, // rot=2
	2, 0  // rot=3
};

float x = 5;
float y = 0;
float fallSpeed = 1.0f;
int rotation = 0;
bool shouldReset = false;
float shouldResetTimer = 0.0f;
std::vector<int> garbage;
int points = 0;
int level = 1;
int totalLineCount = 0;

bool isBlockValid(int x, int y) {
	if (y >= 19) { shouldReset = true; return false; }
	else if (x <= 0 || x >= 11) { return false; }
	for (int i = 0; i < garbage.size() / 6; i++) {
		if (round(x) == round(garbage[i * 6]) && round(y) == round(garbage[(i * 6) + 1] - 1)) {
			return false;
		}
	}
	return true;
}

bool isPieceValid(int x, int y, int block[20]) {
	for (int i = 0; i < 4; i++) {
		if (!isBlockValid(x + block[i * 2], y + block[(i * 2) + 1])) { return false; }
	}
	return true;
}

bool TisBlockValid(int x, int y) {
	if (y >= 19) { return false; }
	else if (x <= 0 || x >= 11) { return false; }
	for (int i = 0; i < garbage.size() / 6; i++) {
		if (round(x) == round(garbage[i * 6]) && round(y) == round(garbage[(i * 6) + 1] - 1)) {
			return false;
		}
	}
	return true;
}

bool TisPieceValid(int x, int y, int block[20]) {
	for (int i = 0; i < 4; i++) {
		if (!TisBlockValid(x + block[i * 2], y + block[(i * 2) + 1])) { return false; }
	}
	return true;
}

int main()
{
	initGraphics();

	float bx = 40;
	Window win(12 * bx, 21 * bx, "grey");
	win.setFlag(WINDOW_RESIZABLE, false);
	win.debugInfo = false;
	win.open();
	int currentBlock[20];
	for (int i = 0; i < 20; i++) { currentBlock[i] = SQUARE_BLOCK[i]; }

	TextureID block = win.newTexture("resources/block.png");

	while (win.isOpen) {
		win.update();

		srand(glfwGetTime() * 100);

		if (shouldReset) {
			shouldResetTimer += win.getDeltaTime() * fallSpeed * 2;
			if (shouldResetTimer > 1.0f / fallSpeed) {
				for (int i = 0; i < 4; i++) {
					garbage.push_back(x + currentBlock[i * 2]);
					garbage.push_back(y + currentBlock[(i * 2) + 1] + 1);
					for (int z = 0; z < 4; z++) {
						garbage.push_back(currentBlock[8 + z]);
					}
				}
				x = 5; y = 0;
				rotation = 0;
				int random = rand() % 7 + 1;
				switch (random) {
				case 1:
					for (int i = 0; i < 20; i++) { currentBlock[i] = LINE_BLOCK[i]; }
					break;
				case 2:
					for (int i = 0; i < 20; i++) { currentBlock[i] = J_BLOCK[i]; }
					break;
				case 3:
					for (int i = 0; i < 20; i++) { currentBlock[i] = L_BLOCK[i]; }
					break;
				case 4:
					for (int i = 0; i < 20; i++) { currentBlock[i] = SQUARE_BLOCK[i]; }
					break;
				case 5:
					for (int i = 0; i < 20; i++) { currentBlock[i] = S_BLOCK[i]; }
					break;
				case 6:
					for (int i = 0; i < 20; i++) { currentBlock[i] = T_BLOCK[i]; }
					break;
				case 7:
					for (int i = 0; i < 20; i++) { currentBlock[i] = Z_BLOCK[i]; }
					break;
				}
				shouldReset = false;
				shouldResetTimer = 0.0f;

				// GARBAGE DAY?
				int table[20] = { 0 };
				for (int i = 0; i < garbage.size() / 6; i++) {
					table[garbage[i * 6 + 1]] += 1;
				}
				int lineCount = 0;
				for (int i = 0; i < 20; i++) {
					if (table[i] >= 10) {
						lineCount += 1;
						for (int z = 0; z < garbage.size() / 6; z++) {
							if (garbage[z * 6 + 1] == i) {
								garbage[z * 6 + 1] = 30;
							}
							else if (garbage[z * 6 + 1] < i) {
								garbage[z * 6 + 1] += 1;
							}
						}
					}
				}
				totalLineCount += lineCount;
				if (lineCount == 1) {
					points += 100 * (level * 0.25f);
				}
				else if (lineCount > 1) {
					points += (lineCount - 1) * 250 * (level * 0.5f);
				}
				for (int i = 0; i < garbage.size() / 6; i++) {
					if (garbage[i * 6 + 1] == 30) {
						garbage.erase(garbage.begin() + (i * 6), garbage.begin() + (i * 6) + 6);
					}
				}
				if (!isPieceValid(x, y, currentBlock)) {
					garbage.clear();
					points = 0;
					level = 1;
					totalLineCount = 0;
					fallSpeed = 1.0f;
					rotation = 0;
					shouldReset = false;
					shouldResetTimer = 0.0f;
				}
			}
		}

		level = (totalLineCount / 10) + 1;
		fallSpeed = 0.5f + (level * 0.5f);
		std::stringstream s;
		s << "grey (points: " << points << ", level: " << level << ", total lines cleared: " << totalLineCount << ")";
		win.setWindowTitle(s.str());

		if (win.isKeyPressed(KEY_LEFT) || win.isKeyPressed(KEY_A)) { if (isPieceValid(x - 1, y, currentBlock)) { x -= 1; } }
		if (win.isKeyPressed(KEY_RIGHT) || win.isKeyPressed(KEY_D)) { if (isPieceValid(x + 1, y, currentBlock)) { x += 1; } }
		if (win.isKeyDown(KEY_DOWN) || win.isKeyDown(KEY_S)) { if (isPieceValid(x, y + (10 * win.getDeltaTime() * fallSpeed), currentBlock)) { y += 10 * win.getDeltaTime(); shouldReset = false; } }
		if (win.isKeyPressed(KEY_UP) || win.isKeyPressed(KEY_W)) {
			int tempBlock[20]; for (int i = 0; i < 20; i++) { tempBlock[i] = currentBlock[i]; }
			float tempX = x; float tempY = y; int tempRotation = rotation;
			if (rotation >= 3) { rotation = 0; }
			else { rotation += 1; }
			for (int i = 0; i < 4; i++) {
				int tx = currentBlock[i * 2];
				currentBlock[i * 2] = 3 - currentBlock[(i * 2) + 1];
				currentBlock[(i * 2) + 1] = tx;
			}
			x += currentBlock[12 + (2 * rotation)];
			y += currentBlock[(12 + (2 * rotation)) + 1];
			if (!isPieceValid(x, y, currentBlock)) {
				for (int i = 0; i < 20; i++) {
					currentBlock[i] = tempBlock[i];
				}
				x = tempX; y = tempY; rotation = tempRotation;
			}
		}

		if (isPieceValid(x, y + fallSpeed * win.getDeltaTime(), currentBlock)) { y += fallSpeed * win.getDeltaTime(); shouldReset = false; }
		else { shouldReset = true; }

		// Draw grid
		for (int i = 0; i < 12; i++) {
			for (int z = 0; z < 21; z++) {
				if (i == 0 || z == 20 || i == 11) {
					win.drawTexture(block, bx * i, bx * z, bx, bx, Color{ 100, 100, 100, 255 });
				}
				else {
					if (i % 2) {
						win.drawTexture(block, bx * i, bx * z, bx, bx, Color{ 50, 50, 50, 255 });
					}
					else {
						win.drawTexture(block, bx * i, bx * z, bx, bx, Color{ 30, 30, 30, 255 });
					}
				}
			}
		}

		// Draw player
		for (int i = 0; i < 4; i++) {
			win.drawTexture(block, (x * bx) + currentBlock[i * 2] * bx, (round(y) * bx) + currentBlock[(i * 2) + 1] * bx, bx, bx, Color{ currentBlock[8], currentBlock[9], currentBlock[10], currentBlock[11] });
		}

		// Draw garbage
		for (int i = 0; i < garbage.size() / 6; i++) {
			win.drawTexture(block, garbage[i * 6] * bx, garbage[i * 6 + 1] * bx, bx, bx, Color{ garbage[i * 6 + 2], garbage[i * 6 + 3], garbage[i * 6 + 4], garbage[i * 6 + 5] });
		}

		// Draw ghost player
		/*float farthestY = y;
		while (TisPieceValid(x, farthestY, currentBlock)) {
			farthestY += 1;
		}
		farthestY -= 1;
		for (int i = 0; i < 4; i++) {
			win.drawTexture(block, (x * bx) + currentBlock[i * 2] * bx, (round(farthestY) * bx) + currentBlock[(i * 2) + 1] * bx, bx, bx, Color{ 255, 255, 255, 100 });
		}*/

		win.render();
	}

	win.close();
	closeGraphics();
}