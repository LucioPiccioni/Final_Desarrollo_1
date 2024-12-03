#include "music.h"

namespace SOUND_TRACKS
{
	float volume = 0.5;

	GameMusic music = {};

	void init()
	{
		music.mainMenu = LoadMusicStream("res/music/Louie's Lullaby - Harris Cole.mp3");
		music.gamePlay = LoadMusicStream("res/music/Breathtaking - Purrple Cat.mp3");
		music.gameOver = LoadMusicStream("res/music/JEN - QUIET NIGHTS - soulmate.mp3");
	}

	void unload()
	{
		UnloadMusicStream(music.mainMenu);
		UnloadMusicStream(music.gamePlay);
		UnloadMusicStream(music.gameOver);
	}

	void MusicControl(PROGRAM_MANAGER::State_Manager& state_Manager)
	{
		const int AllMusic = 2;

		Music* actualMusic = nullptr;
		Music* stopMusic[AllMusic] = { nullptr };

		switch (state_Manager.actual)
		{
		case PROGRAM_MANAGER::Program_State::MAIN_MENU:

			MainMenuOrganization(actualMusic, stopMusic);
			break;

		case PROGRAM_MANAGER::Program_State::GAMEPLAY:
		case PROGRAM_MANAGER::Program_State::PAUSE:

			GamePlayOrganization(actualMusic, stopMusic);
			break;

		case PROGRAM_MANAGER::Program_State::GAME_OVER:

			GameOverOrganization(actualMusic, stopMusic);
			break;

		case PROGRAM_MANAGER::Program_State::RULES:

			MainMenuOrganization(actualMusic, stopMusic);
			break;

		case PROGRAM_MANAGER::Program_State::CREDITS:

			MainMenuOrganization(actualMusic, stopMusic);
			break;

		case PROGRAM_MANAGER::Program_State::WANT_TO_EXIT:

			if (state_Manager.previus == PROGRAM_MANAGER::Program_State::MAIN_MENU)
				MainMenuOrganization(actualMusic, stopMusic);
			else if (state_Manager.previus == PROGRAM_MANAGER::Program_State::GAME_OVER)
				GameOverOrganization(actualMusic, stopMusic);
			else
				GamePlayOrganization(actualMusic, stopMusic);
			break;

		default:
			break;
		}

		for (int i = 0; i < AllMusic; i++)
		{
			if (stopMusic[i] != nullptr)
			{
				if (IsMusicStreamPlaying(*stopMusic[i]))
					StopMusicStream(*stopMusic[i]);
			}
		}

		if (actualMusic != nullptr)
		{
			SetMusicVolume(*actualMusic, volume);

			if (!IsMusicStreamPlaying(*actualMusic))
				PlayMusicStream(*actualMusic);

			UpdateMusicStream(*actualMusic);
		}
	}

	void MainMenuOrganization(Music*& actualMusic, Music* stopMusic[])
	{
		actualMusic = &music.mainMenu;

		stopMusic[0] = &music.gamePlay;
		stopMusic[1] = &music.gameOver;
	}

	void GamePlayOrganization(Music*& actualMusic, Music* stopMusic[])
	{
		actualMusic = &music.gamePlay;

		stopMusic[0] = &music.mainMenu;
		stopMusic[1] = &music.gameOver;
	}

	void GameOverOrganization(Music*& actualMusic, Music* stopMusic[])
	{
		actualMusic = &music.gameOver;

		stopMusic[0] = &music.mainMenu;
		stopMusic[1] = &music.gamePlay;
	}
}