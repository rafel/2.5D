#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <iostream>
#include <string>

#include "irrKlang/irrKlang.h"
#pragma comment(lib, "irrklang.lib")

using namespace std;
using namespace irrklang;

class AudioPlayer
{
private:
	ISoundEngine* soundEngine;
	ISound* currentSound;
	string fileName;
	int volume;
	int position;

public:
	AudioPlayer();
	AudioPlayer(string soundFile); // Doesn't play sound, only initializes fileName
	~AudioPlayer();

	/* All play functions STOP execution of the program except
	* playSoundThreaded(). Note: It isn't really multi-threaded.
	*/

	void playSound(); // Plays entire sound file
	void playSound(int milliseconds); // Plays for X number of milliseconds
	void playSound(string soundFile); // Play entire specified sound file
	void playSound(string soundFile, int milliseconds);
	void playSoundThreaded(); // Starts playing sound but program continues
	bool isSoundPlaying(); // True = music is playing

	// Pause/Resume, works like any other media player
	void pause();
	void resume();

	// Set/get sound file to be played/playing
	void setFileName(string soundFile);
	string getFileName();

	// Volume controls
	void setVolume(int newVolume);
	void increaseVolume();
	void increaseVolume(int increment);
	void decreaseVolume();
	void decreaseVolume(int increment);
	int getCurrentVolume();
		
};

#endif