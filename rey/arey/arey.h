#define _CRT_SECURE_NO_DEPRECATE
#include <AL/al.h>
#include <AL/alc.h>
#include <stddef.h>
#include <iostream>
#include <AL/alext.h>
#include <vorbis/vorbisfile.h>

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

//Audio loadAudioOgg(const char* path) {
//	ALenum error = 0;
//	ALuint* sound = 0;
//	FILE* fp = 0;
//	OggVorbis_File vf;
//	vorbis_info* vi = 0;
//	ALenum format = 0;
//	short* pcmout = 0;
//
//	// open the file in read binary mode
//	fp = fopen(path, "rb");
//	if (fp == 0) {
//		fprintf(stderr, "Could not open file `%s`\n", path);
//		free(pcmout);
//		free(sound);
//		fclose(fp);
//		ov_clear(&vf);
//		return 0;
//	}
//
//	// make a handle
//	sound = new ALuint;
//	if (sound == 0) {
//		fprintf(stderr, "Out of memory.");
//		free(pcmout);
//		free(sound);
//		fclose(fp);
//		ov_clear(&vf);
//		return 0;
//	}
//
//	// make a buffer
//	alGenBuffers(1, sound);
//
//	// check for errors
//	if ((error = alGetError()) != AL_NO_ERROR) {
//		fprintf(stderr, "Failed to generate sound buffer %d\n", error);
//		free(pcmout);
//		free(sound);
//		fclose(fp);
//		ov_clear(&vf);
//		return 0;
//	}
//
//	// open the ogg vorbis file. This is a must on windows, do not use ov_open.
//  // set OV_CALLBACKS_NOCLOSE else it will close your fp when ov_close() is reached, which is fine.
//	if (ov_open_callbacks(fp, &vf, NULL, 0, OV_CALLBACKS_NOCLOSE) < 0) {
//		fprintf(stderr, "Stream is not a valid OggVorbis stream!\n");
//		free(pcmout);
//		free(sound);
//		fclose(fp);
//		ov_clear(&vf);
//		return 0;
//	}
//
//
//	// fill vi with a new ogg vorbis info struct, determine audio format
//	// audio format will always been a length of 16bits, vi->channels determines mono or stereo
//	vi = ov_info(&vf, -1);
//	format = vi->channels == 1 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
//
//	// data_len is the amount of data to read, allocate said data space
//	// this is calculated by (samples * channels * 2 (aka 16bits))
//	size_t data_len = ov_pcm_total(&vf, -1) * vi->channels * 2;
//	pcmout = new short[(int)data_len/sizeof(short)];
//	if (pcmout == 0) {
//		fprintf(stderr, "Out of memory.\n");
//		free(pcmout);
//		free(sound);
//		fclose(fp);
//		ov_clear(&vf);
//		return 0;
//	}
//
//	// fill pcmout buffer with ov_read data samples
//	// you can't just slap data_len in place of 4096, it doesn't work that way
//	// 0 is endianess, 0 for little, 1 for big
//	// 2 is the data type short's size, mine is 2
//	// 1 is the signedness you want, I want short not unsigned short (for openal) so 1
//	for (size_t size = 0, offset = 0, sel = 0;
//		(size = ov_read(&vf, (char*)pcmout + offset, 4096, 0, 2, 1, (int*)&sel)) != 0;
//		offset += size) {
//		if (size < 0)
//			puts("Faulty ogg file :o"); // use https://xiph.org/vorbis/doc/vorbisfile/ov_read.html for handling enums
//	}
//
//	// send data to openal, vi->rate is your freq in Hz, dont assume 44100
//	alBufferData(*sound, format, pcmout, data_len, vi->rate);
//	if ((error = alGetError()) != AL_NO_ERROR) {
//		printf("Failed to send audio information buffer to OpenAL! 0x%06x\n", error);
//		free(pcmout);
//		free(sound);
//		fclose(fp);
//		ov_clear(&vf);
//		return 0;
//	}
//
//	// free your resources >:(
//	free(pcmout);
//	fclose(fp);
//	ov_clear(&vf);
//	return sound;
//}
//
//void playAudio(Audio a) {
//	alSourcePlay((ALuint)a);
//}


void closeAudio() {
	isInit = false;
	alcMakeContextCurrent(NULL);                                                //Make no context current
	alcDestroyContext(context);                                                 //Destroy the OpenAL Context
	alcCloseDevice(device);
}