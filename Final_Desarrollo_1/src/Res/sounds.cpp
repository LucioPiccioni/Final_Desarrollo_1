#include "sounds.h"

#include "music.h"

namespace SOUND
{
	GameSounds gameSounds = {};

	void init()
	{
		gameSounds.button = LoadSound("res/soundEffects/button.wav");
		gameSounds.jump  = LoadSound("res/soundEffects/jump.wav");
		gameSounds.point = LoadSound("res/soundEffects/point.wav");
		gameSounds.die = LoadSound("res/soundEffects/loose.wav");
	}

	void volumeManager()
	{
	
		SetSoundVolume(gameSounds.button, SOUND_TRACKS::volume);
		SetSoundVolume(gameSounds.jump, SOUND_TRACKS::volume);
		SetSoundVolume(gameSounds.point, SOUND_TRACKS::volume);
		SetSoundVolume(gameSounds.die, SOUND_TRACKS::volume);
	}

	void unload()
	{
		UnloadSound(gameSounds.button);
		UnloadSound(gameSounds.jump);
		UnloadSound(gameSounds.point);
		UnloadSound(gameSounds.die);
	}
}
