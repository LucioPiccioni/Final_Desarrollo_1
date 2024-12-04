#pragma once
#include "raylib.h"

namespace SOUND
{
	struct GameSounds
	{
		Sound button = {};
		Sound jump = {};
		Sound point = {};
		Sound die = {};
	};

	extern GameSounds game_Sounds;

	void init();

	void volumeManager();

	void unload();
}