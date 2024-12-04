#include "game_over.h"

#include "Program/program_Data.h"
#include "Program/Utilities/button.h"

#include "Gameplay/gameplay.h"

#include "Res/sounds.h"
#include "Res/sprites.h"

namespace GAME_OVER
{
	const int maxButtons = 3;
	Vector2 mouse;
	BUTTON::Button buttons[maxButtons] = {};

	void init()
	{
		float startX = (static_cast<float>(PROGRAM_DATA::screen_Width) - BUTTON::width) / 2;
		float startY = ((PROGRAM_DATA::screen_Height - PROGRAM_DATA::screen_Height / 5) - (BUTTON::height * maxButtons + BUTTON::spacing * (maxButtons - 1)));

		for (int i = 0; i < maxButtons; i++)
		{
			buttons[i].rect = { startX, startY + i * (BUTTON::height + BUTTON::spacing), BUTTON::width, BUTTON::height };
		}

		buttons[0].option = PROGRAM_MANAGER::Program_State::REPLAY;
		buttons[1].option = PROGRAM_MANAGER::Program_State::MAIN_MENU;
		buttons[2].option = PROGRAM_MANAGER::Program_State::WANT_TO_EXIT;

		buttons[0].text = "REPLAY";
		buttons[1].text = "MENU";
		buttons[2].text = "EXIT";
	}

	void update(PROGRAM_MANAGER::State_Manager& state_Manager)
	{
		mouse = GetMousePosition();

		SPRITE::update_Paralax_Pos(GetFrameTime());

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

		if (state_Manager.actual == PROGRAM_MANAGER::Program_State::REPLAY)
		{
			GAMEPLAY::init();
			state_Manager.actual = PROGRAM_MANAGER::Program_State::GAMEPLAY;
		}
		else if (state_Manager.actual == PROGRAM_MANAGER::Program_State::MAIN_MENU)
		{
			GAMEPLAY::init();
		}
		else if (state_Manager.actual == PROGRAM_MANAGER::Program_State::WANT_TO_EXIT)
		{
			state_Manager.previus = PROGRAM_MANAGER::Program_State::GAME_OVER;
		}
	}

	void draw(Font font)
	{
		Vector2 gameOverTextSize = MeasureTextEx(font, "GAME OVER", BUTTON::titles_Font_Size, 0);
		Vector2 gameOverPos = { (static_cast<float>(PROGRAM_DATA::screen_Width) - gameOverTextSize.x) * 0.5f, gameOverTextSize.y };

		SPRITE::draw_Paralax();

		DrawRectangle(0, 0, 
			static_cast<int>(PROGRAM_DATA::screen_Width), 
			static_cast<int>(PROGRAM_DATA::screen_Height), Color{ 0, 0, 0, 125 });

		DrawTextEx(font, "GAME OVER", gameOverPos, BUTTON::titles_Font_Size, 0, RED);

		for (int i = 0; i < maxButtons; i++)
		{
			BUTTON::drawButton(buttons[i], font);
		}
	}
}

