#include "confirm_exit.h"

#include "Program/program_Data.h"
#include "Program/program_Manager.h"
#include "Program/Utilities/button.h"

#include "Res/sounds.h"
#include "Res/sprites.h"

namespace CONFIRM_EXIT
{
	const int maxButtons = 2;
	BUTTON::Button button[maxButtons];
	Vector2 mouse;

	void CONFIRM_EXIT::init()
	{
		float startX;
		float startY;

		startX = (
			PROGRAM_DATA::screenWidth -BUTTON::width) * 0.5f;
		startY = (PROGRAM_DATA::screenHeight - (BUTTON::height * maxButtons + BUTTON::spacing * (maxButtons - 1))) / 2;

		button[0].option = PROGRAM_MANAGER::Program_State::CONFIRM_EXIT;
		button[1].option = PROGRAM_MANAGER::Program_State::CANCEL_EXIT;

		button[0].text = "Leave";
		button[1].text = "Stay";

		for (int i = 0; i < maxButtons; i++)
		{
			button[i].rect = { static_cast<float>(startX), static_cast<float>(startY + i * (BUTTON::height + BUTTON::spacing)), BUTTON::width, BUTTON::height };

			switch (button[i].option)
			{
			case PROGRAM_MANAGER::Program_State::CONFIRM_EXIT:
				button[i].color = RED;
				break;

			case PROGRAM_MANAGER::Program_State::CANCEL_EXIT:
				button[i].color = GREEN;
				break;

			default:
				break;
			}
		}
	}

	void update(PROGRAM_MANAGER::State_Manager& state_manager)
	{
		mouse = GetMousePosition();

		SPRITE::update_Paralax_Pos(GetFrameTime());

		for (int i = 0; i < maxButtons; i++)
		{
			if (BUTTON::isButtonClicked(mouse, button[i]))
			{
				button[i].color = WHITE;

				if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
				{
					button[i].color = YELLOW;
				}

				if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				{
					StopSound(SOUND::gameSounds.button);
					PlaySound(SOUND::gameSounds.button);
					state_manager.actual = button[i].option;
				}
			}
			else
			{
				button[i].color = BUTTON::button_Default_Color;
			}
		}

		switch (state_manager.actual)
		{
		case PROGRAM_MANAGER::Program_State::CONFIRM_EXIT:

			state_manager.actual = PROGRAM_MANAGER::Program_State::CONFIRM_EXIT;
			break;

		case PROGRAM_MANAGER::Program_State::CANCEL_EXIT:

			state_manager.actual = state_manager.previus;
			//timmerToCleanBuffer = 0.01f;
			break;

		default:
			break;
		}
	}

	void draw(Font font)
	{
		SPRITE::draw_Paralax();

		DrawRectangle(0, 0, 
			static_cast<int>(PROGRAM_DATA::screenWidth), 
			static_cast<int>(PROGRAM_DATA::screenHeight), 
			Color{ 0, 0, 0, 225 });

		DrawTextEx(font, "Are you sure you want to exit?",
			Vector2{ static_cast<float>(PROGRAM_DATA::screenWidth) / 2 - MeasureTextEx(font, "Are you sure you want to exit?", BUTTON::textFontSize, 0).x / 2, static_cast<float>(PROGRAM_DATA::screenHeight / 4) },
			BUTTON::textFontSize, 0, RED);

		for (int i = 0; i < maxButtons; i++)
		{
			BUTTON::drawButton(button[i], font);
		}
	}
}
