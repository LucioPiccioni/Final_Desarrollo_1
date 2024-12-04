#include "main_menu.h"

#include "Program/Utilities/button.h"
#include "Program/program_Data.h"

#include "Res/sounds.h"
#include "Res/music.h"
#include "Res/sprites.h"

namespace MAIN_MENU
{
	static const int maxButtons = 4;
	static BUTTON::Button buttons[maxButtons];

	void initializeMenu()
	{
		init();
	}

	void update(PROGRAM_MANAGER::State_Manager& state_manager, float delta_Time)
	{
		Vector2 mouse = GetMousePosition();

		SPRITE::update_Paralax_Pos(delta_Time);

		if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_LEFT)) && SOUND_TRACKS::volume > 0)
			SOUND_TRACKS::volume -= 0.1f * delta_Time;
		else if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_RIGHT)) && SOUND_TRACKS::volume < 1)
			SOUND_TRACKS::volume += 0.1f * delta_Time;

		if (SOUND_TRACKS::volume > 1)
			SOUND_TRACKS::volume = 1;
		else if (SOUND_TRACKS::volume < 0)
			SOUND_TRACKS::volume = 0;

		for (int i = 0; i < maxButtons; i++)
		{
			if (BUTTON::isButtonClicked(mouse, buttons[i]))
			{
				buttons[i].color = WHITE;

				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					buttons[i].color = YELLOW;
				}

				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				{
					StopSound(SOUND::gameSounds.button);
					PlaySound(SOUND::gameSounds.button);
					state_manager.actual = buttons[i].option;
				}
			}
			else
			{
				buttons[i].color = BUTTON::button_Default_Color;
			}
		}

		if (state_manager.actual == PROGRAM_MANAGER::Program_State::WANT_TO_EXIT)
		{
			state_manager.previus = PROGRAM_MANAGER::Program_State::MAIN_MENU;
		}

		SPRITE::update_Paralax_Pos(GetFrameTime());
	}

	void draw(Font font)
	{
		SPRITE::draw_Paralax();

		DrawRectangle(0, 0, static_cast<int>(PROGRAM_DATA::screenWidth),
			static_cast<int>(PROGRAM_DATA::screenHeight), Color{ 0, 0, 0, 125 });

		DrawText("v1.0", 0, 0, 20, WHITE);

		DrawTextPro(font,
			"The Spark",
			Vector2{ (PROGRAM_DATA::screenWidth - MeasureTextEx(font, "The Spark", BUTTON::titlesFontSize, 0).x) * 0.5f,
					 MeasureTextEx(font, "The Spark", BUTTON::titlesFontSize, 0).y * 0.5f },
			Vector2{ 0, 0 },
			0, BUTTON::titlesFontSize,
			0,
			YELLOW);

		for (int i = 0; i < maxButtons; i++)
		{
			BUTTON::drawButton(buttons[i], font);
		}

		DrawText("Hold Left/Down to lower volume,", 10, static_cast<int>(PROGRAM_DATA::screenHeight) - 60, 14, WHITE);
		DrawText("Right/Up to increase volume", 10, static_cast<int>(PROGRAM_DATA::screenHeight) - 40, 14, WHITE);

		int volumePercentage = static_cast<int>(SOUND_TRACKS::volume * 100);
		DrawText(("Volume: " + std::to_string(volumePercentage) + "%").c_str(), 10,
			static_cast<int>(PROGRAM_DATA::screenHeight) - 20, 14, WHITE);
	}


	void init()
	{
		float startX = (PROGRAM_DATA::screenWidth - BUTTON::width) / 2;
		float startY = (PROGRAM_DATA::screenHeight - BUTTON::height) - (BUTTON::height * maxButtons + BUTTON::spacing * (maxButtons - 1));

		for (int i = 0; i < maxButtons; i++)
		{
			buttons[i].rect = { startX, startY + i * (BUTTON::height + BUTTON::spacing), BUTTON::width, BUTTON::height };
			buttons[i].color = BLACK;
		}

		buttons[0].option = PROGRAM_MANAGER::Program_State::GAMEPLAY;
		buttons[1].option = PROGRAM_MANAGER::Program_State::RULES;
		buttons[2].option = PROGRAM_MANAGER::Program_State::CREDITS;
		buttons[3].option = PROGRAM_MANAGER::Program_State::WANT_TO_EXIT;

		buttons[0].text = "GAMEPLAY";
		buttons[1].text = "RULES";
		buttons[2].text = "CREDITS";
		buttons[3].text = "EXIT";

	}

}

