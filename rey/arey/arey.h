#include <AL/al.h>
#include <AL/alc.h>
#include <stddef.h>
#include <iostream>
#include <AL/alext.h>

ALCcontext* context;
ALCdevice* device;
bool isInit = false;
int bufferIndex = 1;
typedef ALuint* Audio;

bool initAudio() {
	device = alcOpenDevice(NULL);
	if (device == NULL)
	{
		return false;
	}

	//Create a context
	context = alcCreateContext(device, NULL);

	//Set active context
	alcMakeContextCurrent(context);

	// Clear Error Code
	alGetError();
	isInit = true;
	return true;
}

void checkInit() {
	if (!isInit) std::cout << "All rey modules must be initialized before use." << std::endl;
}



void closeAudio() {
	isInit = false;
	alcMakeContextCurrent(NULL);                                                //Make no context current
	alcDestroyContext(context);                                                 //Destroy the OpenAL Context
	alcCloseDevice(device);
}