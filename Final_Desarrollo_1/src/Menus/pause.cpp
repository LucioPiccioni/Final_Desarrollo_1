#include "pause.h"

#include "Program/program_Data.h"
#include "Program/Utilities/button.h"

#include "Gameplay/gameplay.h"

#include "Res/sounds.h"

namespace PAUSE
{
	const int buttonCount = 3;
	Vector2 mouse;
	BUTTON::Button buttons[buttonCount] = {};

	void init()
	{
		float startX = (PROGRAM_DATA::screen_Width - BUTTON::width) / 2;
		float startY = (PROGRAM_DATA::screen_Height - BUTTON::height) - (BUTTON::height * buttonCount + BUTTON::spacing * (buttonCount - 1));


		buttons[0].option = PROGRAM_MANAGER::Program_State::GAMEPLAY;
		buttons[1].option = PROGRAM_MANAGER::Program_State::MAIN_MENU;
		buttons[2].option = PROGRAM_MANAGER::Program_State::WANT_TO_EXIT;

		buttons[0].text = "RESUME";
		buttons[1].text = "MENU";
		buttons[2].text = "EXIT";

		Color outline = BLACK;

		for (int i = 0; i < buttonCount; i++)
		{
			buttons[i].rect = { startX, startY + i * (BUTTON::height + BUTTON::spacing), BUTTON::width, BUTTON::height };
			buttons[i].outline = outline;
		}

	}

	void update(PROGRAM_MANAGER::State_Manager& state_Manager)
	{
		mouse = GetMousePosition();

		if (IsKeyPressed(KEY_ESCAPE))
			state_Manager.actual = state_Manager.previus;

		for (int i = 0; i < buttonCount; i++)
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
					StopSound(SOUND::game_Sounds.button);
					PlaySound(SOUND::game_Sounds.button);
					state_Manager.actual = buttons[i].option;
				}
			}
			else
			{
				buttons[i].color = BUTTON::button_Default_Color;
			}
		}

		if (state_Manager.actual == PROGRAM_MANAGER::Program_State::MAIN_MENU)
		{
			GAMEPLAY::init();
		}
		else if (state_Manager.actual == PROGRAM_MANAGER::Program_State::WANT_TO_EXIT)
		{
			state_Manager.previus = PROGRAM_MANAGER::Program_State::PAUSE;
		}
	}

	void draw(Font font)
	{
		GAMEPLAY::draw(font);

		Vector2 titlePos =
		{
			(PROGRAM_DATA::screen_Width) / 2 - MeasureTextEx(font, "Pause", BUTTON::titles_Font_Size, 2).x / 2,
			(PROGRAM_DATA::screen_Height) / 5
		};

		Color pastelPurple = { 214, 196, 224, 255 };

		DrawRectangle(0, 0,
			static_cast<int>(PROGRAM_DATA::screen_Width),
			static_cast<int>(PROGRAM_DATA::screen_Height), Color{ 0, 0, 0, 125 });

		DrawTextEx(font, "Pause", titlePos, BUTTON::titles_Font_Size, 2, pastelPurple);

		for (int i = 0; i < buttonCount; i++)
		{
			BUTTON::drawButton(buttons[i], font);
		}
	}
}

