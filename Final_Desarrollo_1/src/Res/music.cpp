#include "music.h"

namespace SOUND_TRACKS
{
	float volume = 0.5;

	GameMusic music = {};

	void init()
	{
		music.main_Menu = LoadMusicStream("res/music/Louie's Lullaby - Harris Cole.mp3");
		music.gameplay = LoadMusicStream("res/music/Breathtaking - Purrple Cat.mp3");
		music.game_Over = LoadMusicStream("res/music/JEN - QUIET NIGHTS - soulmate.mp3");
	}

	void unload()
	{
		UnloadMusicStream(music.main_Menu);
		UnloadMusicStream(music.gameplay);
		UnloadMusicStream(music.game_Over);
	}

	void MusicControl(PROGRAM_MANAGER::State_Manager& state_Manager)
	{
		const int AllMusic = 2;

		Music* actual_Music = nullptr;
		Music* stop_Music[AllMusic] = { nullptr };

		switch (state_Manager.actual)
		{
		case PROGRAM_MANAGER::Program_State::MAIN_MENU:

			MainMenuOrganization(actual_Music, stop_Music);
			break;

		case PROGRAM_MANAGER::Program_State::GAMEPLAY:
		case PROGRAM_MANAGER::Program_State::PAUSE:

			GamePlayOrganization(actual_Music, stop_Music);
			break;

		case PROGRAM_MANAGER::Program_State::GAME_OVER:

			GameOverOrganization(actual_Music, stop_Music);
			break;

		case PROGRAM_MANAGER::Program_State::RULES:

			MainMenuOrganization(actual_Music, stop_Music);
			break;

		case PROGRAM_MANAGER::Program_State::CREDITS:

			MainMenuOrganization(actual_Music, stop_Music);
			break;

		case PROGRAM_MANAGER::Program_State::WANT_TO_EXIT:

			if (state_Manager.previus == PROGRAM_MANAGER::Program_State::MAIN_MENU)
				MainMenuOrganization(actual_Music, stop_Music);
			else if (state_Manager.previus == PROGRAM_MANAGER::Program_State::GAME_OVER)
				GameOverOrganization(actual_Music, stop_Music);
			else
				GamePlayOrganization(actual_Music, stop_Music);
			break;

		default:
			break;
		}

		for (int i = 0; i < AllMusic; i++)
		{
			if (stop_Music[i] != nullptr)
			{
				if (IsMusicStreamPlaying(*stop_Music[i]))
					StopMusicStream(*stop_Music[i]);
			}
		}

		if (actual_Music != nullptr)
		{
			SetMusicVolume(*actual_Music, volume);

			if (!IsMusicStreamPlaying(*actual_Music))
				PlayMusicStream(*actual_Music);

			UpdateMusicStream(*actual_Music);
		}
	}

	void MainMenuOrganization(Music*& actual_Music, Music* stop_Music[])
	{
		actual_Music = &music.main_Menu;

		stop_Music[0] = &music.gameplay;
		stop_Music[1] = &music.game_Over;
	}

	void GamePlayOrganization(Music*& actual_Music, Music* stop_Music[])
	{
		actual_Music = &music.gameplay;

		stop_Music[0] = &music.main_Menu;
		stop_Music[1] = &music.game_Over;
	}

	void GameOverOrganization(Music*& actual_Music, Music* stop_Music[])
	{
		actual_Music = &music.game_Over;

		stop_Music[0] = &music.main_Menu;
		stop_Music[1] = &music.gameplay;
	}
}