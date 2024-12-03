#pragma once
#include "raylib.h"

#include "program_Manager.h"

namespace SOUND_TRACKS
{
	extern float volume;

	struct GameMusic
	{
		Music mainMenu = {};
		Music gameOver = {};
		Music gamePlay = {};
	};

	extern GameMusic music;

	void init();
	void unload();

	void MusicControl(PROGRAM_MANAGER::State_Manager& state_Manager);

	void MainMenuOrganization(Music*& actualMusic, Music* stopMusic[]);
	void GamePlayOrganization(Music*& actualMusic, Music* stopMusic[]);
	void GameOverOrganization(Music*& actualMusic, Music* stopMusic[]);
}