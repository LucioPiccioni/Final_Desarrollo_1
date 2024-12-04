#pragma once
#include "raylib.h"

#include "Program/program_Manager.h"

namespace SOUND_TRACKS
{
	extern float volume;

	struct GameMusic
	{
		Music main_Menu = {};
		Music game_Over = {};
		Music gameplay = {};
	};

	extern GameMusic music;

	void init();
	void unload();

	void MusicControl(PROGRAM_MANAGER::State_Manager& state_Manager);

	void MainMenuOrganization(Music*& actual_Music, Music* stop_Music[]);
	void GamePlayOrganization(Music*& actual_Music, Music* stop_Music[]);
	void GameOverOrganization(Music*& actual_Music, Music* stop_Music[]);
}