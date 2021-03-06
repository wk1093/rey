#include "grey.h"
#include <random>

int main() {
	initGraphics(1);

	Window win(1280, 720, "grey");
	win.open();
	win.setBackgroundColor(COLOR_WHITE);

	int spawnAmountMin = 100;
	int spawnAmountMax = 250;

	srand(glfwGetTime() * 1000);

	class Confetti {
	public:
		float size = 25.0f, confettiX = 50.0f, confettiY = 200.0f, confettiRot = 0.0f, confettiVelX = 100.0f, confettiVelY = -600.0f, fallSpeed = 750.0f, rotRate = -confettiX * 1.5f;
		Color color = COLOR_MAGENTA;
		Confetti(float _size, float _confettiX, float _confettiY, float _confettiRot, float _confettiVelX, float _confettiVelY, float _fallSpeed, Color _color) {
			size = _size;
			confettiX = _confettiX;
			confettiY = _confettiY;
			confettiRot = _confettiRot;
			confettiVelX = _confettiVelX;
			confettiVelY = _confettiVelY;
			fallSpeed = _fallSpeed;
			rotRate = -(250.0f + (rand() % 500));
			color = _color;
			if (_color[0] == _color[1] && _color[1] == _color[2]) {
				std::cout << "Finally! A grey one!\n";
				size = 250;
				rotRate = rotRate / 4;
				fallSpeed = fallSpeed / 4;
			}
		}
	};

	std::vector<Confetti> confetti;
	std::vector<Confetti> rareConfetti;

	TextureID block = win.newTexture("resources/block.png");
	while (win.isOpen) {
		win.update();

		win.drawRect(0, 0, win.width, win.height, COLOR_WHITE);

		if (win.isKeyDown(KEY_SPACE))
			win.wireframe = true;
		else
			win.wireframe = false;
		if (win.isKeyPressed(KEY_R)) {
			confetti = {  };
			rareConfetti = {  };
		}
		if (win.isKeyPressed(KEY_F11))
			win.setFullscreen(!win.fullscreen);
		if (win.isKeyPressed(KEY_ESCAPE))
			win.isOpen = false;
		if (win.isKeyPressed(KEY_C) || win.isMousePressed(MOUSE_LEFT)) {
			for (int i = 0; i < spawnAmountMin + (rand() % (spawnAmountMax - spawnAmountMin) + 1); i++) {
				float min = 250 + (rand() % 750 + 1);
				float max = min + rand() % 500 + 1;
				int r = rand() % 255 + 1, g = rand() % 255 + 1, b = rand() % 255 + 1;
				Confetti c(20 + (rand() % 10 + 1), win.mouseX, win.mouseY, 0.0f, (rand() % 1000 + 1) - 500, -min, max, Color{ r, g, b, 255 });
				if (r == g && g == b) {
					rareConfetti.push_back(c);
				}
				else {
					confetti.push_back(c);
				}
			}
		}

		for (int i = 0; i < confetti.size(); i++) {
			if (confetti[i].confettiY > win.height + 100) {

			}
			else {
				if (confetti[i].confettiY > win.height - confetti[i].size && confetti[i].confettiVelY > 0) {
					confetti[i].confettiVelY -= confetti[i].confettiVelY * 1.65f;
				}
				if (confetti[i].confettiX < 0 || confetti[i].confettiX + confetti[i].size > win.width) {
					confetti[i].confettiVelX -= confetti[i].confettiVelX * 2.0f;
				}
				float fallOff = 100.0f;
				if (confetti[i].confettiVelX > 0) { confetti[i].confettiVelX -= fallOff * win.getDeltaTime(); }
				else { confetti[i].confettiVelX += fallOff * win.getDeltaTime(); }
				float rotationFallOff = 50.0f;
				if (confetti[i].rotRate > 0) { confetti[i].rotRate -= rotationFallOff * win.getDeltaTime(); }
				else { confetti[i].rotRate += rotationFallOff * win.getDeltaTime(); }
				confetti[i].confettiX += confetti[i].confettiVelX * win.getDeltaTime();
				confetti[i].confettiVelY += confetti[i].fallSpeed * win.getDeltaTime();
				confetti[i].confettiY += confetti[i].confettiVelY * win.getDeltaTime();
				confetti[i].confettiRot += confetti[i].rotRate * win.getDeltaTime();

				win.drawTexture(block, confetti[i].confettiX, confetti[i].confettiY, confetti[i].size, confetti[i].size, confetti[i].color, confetti[i].confettiRot);
			}
		}
		for (int i = 0; i < rareConfetti.size(); i++) {
			if (rareConfetti[i].confettiY > win.height + 100) {

			}
			else {
				if (rareConfetti[i].confettiY > win.height - rareConfetti[i].size && rareConfetti[i].confettiVelY > 0) {
					rareConfetti[i].confettiVelY -= rareConfetti[i].confettiVelY * 1.65f;
				}
				if (rareConfetti[i].confettiX < 0 || rareConfetti[i].confettiX + rareConfetti[i].size > win.width) {
					rareConfetti[i].confettiVelX -= rareConfetti[i].confettiVelX * 2.0f;
				}
				float fallOff = 100.0f;
				if (rareConfetti[i].confettiVelX > 0) { rareConfetti[i].confettiVelX -= fallOff * win.getDeltaTime(); }
				else { rareConfetti[i].confettiVelX += fallOff * win.getDeltaTime(); }
				float rotationFallOff = 50.0f;
				if (rareConfetti[i].rotRate > 0) { rareConfetti[i].rotRate -= rotationFallOff * win.getDeltaTime(); }
				else { rareConfetti[i].rotRate += rotationFallOff * win.getDeltaTime(); }
				rareConfetti[i].confettiX += rareConfetti[i].confettiVelX * win.getDeltaTime();
				rareConfetti[i].confettiVelY += rareConfetti[i].fallSpeed * win.getDeltaTime();
				rareConfetti[i].confettiY += rareConfetti[i].confettiVelY * win.getDeltaTime();
				rareConfetti[i].confettiRot += rareConfetti[i].rotRate * win.getDeltaTime();

				win.drawTexture(block, rareConfetti[i].confettiX, rareConfetti[i].confettiY, rareConfetti[i].size, rareConfetti[i].size, rareConfetti[i].color, rareConfetti[i].confettiRot);
			}
		}

		std::cout << "Confetti size: " << confetti.size() + rareConfetti.size() << std::endl;

		win.render();
	}

	win.close();
	closeGraphics();
}