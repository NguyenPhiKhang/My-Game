#ifndef _AUDIO_H
#define _AUDIO_H

#include "dsutil.h"
#include <string>
#include "debug.h"
#include "constants.h"

class Audio
{
private:
	LPDIRECTSOUND8        g_pDS;	// The DirectSound Device
public:
	Audio();
	~Audio();
	bool initialize(HWND hwnd);
	void shutdownDirectSound(void);
	LPDIRECTSOUNDBUFFER LoadWaveToSoundBuffer(std::string wavFilename);
	void playSound(LPDIRECTSOUNDBUFFER whichBuffer);
	void playSoundLoop(LPDIRECTSOUNDBUFFER whichBuffer);
	void stopSound(LPDIRECTSOUNDBUFFER whichBuffer);
};

#endif