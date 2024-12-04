#include "sounds.h"

#include "music.h"

namespace SOUND
{
	GameSounds game_Sounds = {};

	void init()
	{
		game_Sounds.button = LoadSound("res/soundEffects/button.wav");
		game_Sounds.jump  = LoadSound("res/soundEffects/jump.wav");
		game_Sounds.point = LoadSound("res/soundEffects/point.wav");
		game_Sounds.die = LoadSound("res/soundEffects/loose.wav");
	}

	void volumeManager()
	{
	
		SetSoundVolume(game_Sounds.button, SOUND_TRACKS::volume);
		SetSoundVolume(game_Sounds.jump, SOUND_TRACKS::volume);
		SetSoundVolume(game_Sounds.point, SOUND_TRACKS::volume);
		SetSoundVolume(game_Sounds.die, SOUND_TRACKS::volume);
	}

	void unload()
	{
		UnloadSound(game_Sounds.button);
		UnloadSound(game_Sounds.jump);
		UnloadSound(game_Sounds.point);
		UnloadSound(game_Sounds.die);
	}
}
