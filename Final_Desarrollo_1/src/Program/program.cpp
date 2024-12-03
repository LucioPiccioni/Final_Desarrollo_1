#include "program.h"

#include "raylib.h"

#include "Program/program_Data.h"
#include "Program/program_Manager.h"

#include "Gameplay/gameplay.h"
#include "Menus/game_over.h"
#include "Menus/main_menu.h"
#include "Menus/rules.h"
#include "Menus/credits.h"
#include "Menus/pause.h"
#include "Menus/confirm_exit.h"
#include "Program/Utilities/button.h"

#include "Res/sprites.h"
#include "Res/sounds.h"
#include "Res/music.h"


namespace PROGRAM
{
	PROGRAM_MANAGER::State_Manager state_manager;
	Font font;

	void init()
	{
		PROGRAM_DATA::screenWidth = 800;
		PROGRAM_DATA::screenHeight = 800;

		state_manager.actual = PROGRAM_MANAGER::Program_State::MAIN_MENU;
		state_manager.previus = PROGRAM_MANAGER::Program_State::MAIN_MENU;

		InitWindow(static_cast<int>(PROGRAM_DATA::screenWidth),
			static_cast<int>(PROGRAM_DATA::screenHeight), "Jumper");

		SetExitKey(0);

		InitAudioDevice();

		font = LoadFontEx("res/Fonts/JLSSpaceGothicR_NC.otf", static_cast<int>(BUTTON::titlesFontSize), 0, 0);

		initMenus();
	}

	void initMenus()
	{
		SOUND_TRACKS::init();
		SOUND::init();
		MAIN_MENU::initializeMenu();
		GAMEPLAY::init();
		GAME_OVER::initButtons();
		SPRITE::init();
		PAUSE::initButtons();
		RULES_MENU::initializeRulesMenu();
		CREDITS_MENU::initializeCreditsMenu();
		CONFIRM_EXIT::initButtons();
	}

	void uninit()
	{
		SOUND_TRACKS::unload();
		SOUND::unload();
		SPRITE::unload();
		CloseAudioDevice();
		UnloadFont(font);
	}

	void update()
	{
		SOUND_TRACKS::MusicControl(state_manager);
		SOUND::volumeManager();

		switch (state_manager.actual)
		{
		case PROGRAM_MANAGER::Program_State::MAIN_MENU:

			MAIN_MENU::update(state_manager, GetFrameTime());
			break;

		case PROGRAM_MANAGER::Program_State::GAMEPLAY:

			GAMEPLAY::update(state_manager);
			break;

		case PROGRAM_MANAGER::Program_State::PAUSE:

			PAUSE::update(state_manager);
			break;

		case PROGRAM_MANAGER::Program_State::GAME_OVER:

			GAME_OVER::update(state_manager);
			break;

		case PROGRAM_MANAGER::Program_State::RULES:

			RULES::update(state_manager);
			break;

		case PROGRAM_MANAGER::Program_State::CREDITS:

			CREDITS::update(state_manager.actual);
			break;

		case PROGRAM_MANAGER::Program_State::WANT_TO_EXIT:

			CONFIRM_EXIT::update(state_manager);
			break;

		default:
			break;
		}
	}

	void draw()
	{
		BeginDrawing();

		ClearBackground(BLACK);

		switch (state_manager.actual)
		{
		case PROGRAM_MANAGER::Program_State::MAIN_MENU:

			MAIN_MENU::drawMenu(font);
			break;

		case PROGRAM_MANAGER::Program_State::GAMEPLAY:

			GAMEPLAY::draw(font);
			break;

		case PROGRAM_MANAGER::Program_State::PAUSE:

			PAUSE::draw(font);
			break;

		case PROGRAM_MANAGER::Program_State::GAME_OVER:

			GAME_OVER::draw(font);
			break;

		case PROGRAM_MANAGER::Program_State::RULES:

			RULES_MENU::drawRulesMenu(font);
			break;

		case PROGRAM_MANAGER::Program_State::CREDITS:

			CREDITS_MENU::drawCreditsMenu(font);
			break;

		case PROGRAM_MANAGER::Program_State::WANT_TO_EXIT:

			CONFIRM_EXIT::draw(font);
			break;

		default:
			break;
		}

		EndDrawing();
	}
}