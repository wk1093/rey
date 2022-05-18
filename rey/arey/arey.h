#include <irrKlang/irrKlang.h>

class AudioClass {
private:
	irrklang::ISoundEngine * sound = irrklang::createIrrKlangDevice();
public:
	void playSound(const char* filePath, bool shouldLoop) {
		sound->play2D(filePath, shouldLoop);
	}
};

AudioClass Audio;