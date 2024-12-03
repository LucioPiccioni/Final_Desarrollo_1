#include "rules.h"

#include "raylib.h"

#include "Program/program_Data.h"
#include "Program/program_Manager.h"
#include "Program/Utilities/button.h"

#include "Res/sounds.h"
#include "Res/sprites.h"

namespace RULES
{
	BUTTON::Button button;

	void init()
	{
		button.text = "Menu";

		button.rect = { ( PROGRAM_DATA::screenWidth - BUTTON::width) * 0.5f ,
			PROGRAM_DATA::screenHeight - BUTTON::height, BUTTON::width,  BUTTON::height };

		button.option = PROGRAM_MANAGER::Program_State::MAIN_MENU;
	}

	void update(PROGRAM_MANAGER::State_Manager& program_Manager)
	{
		Vector2 mouse = GetMousePosition();

		SPRITE::update_Paralax_Pos(GetFrameTime());

		if (BUTTON::isButtonClicked(mouse, button))
		{
			button.color = WHITE;

			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				button.color = YELLOW;
			}

			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				StopSound(SOUND::gameSounds.button);
				PlaySound(SOUND::gameSounds.button);
				program_Manager.actual = PROGRAM_MANAGER::Program_State::MAIN_MENU;
			}
		}
		else
		{
			button.color = BUTTON::button_Default_Color;
		}
	}

	void draw(Font font)
	{
		SPRITE::draw_Paralax();

		DrawRectangle(0, 0, 
			static_cast<int>(PROGRAM_DATA::screenWidth),
			static_cast<int>(PROGRAM_DATA::screenHeight), Color{ 0, 0, 0, 225 });

		DrawTextPro(font, "Rules",
			Vector2{ (GetScreenWidth() - MeasureTextEx(font, "Rules", 40, 0).x) * 0.5f, 50 },
			Vector2{ 0, 0 }, 0, 40, 0, WHITE);

		float textX = 50;
		float textY = 150;
		float spacing = 40;

		DrawTextPro(font, "Gameplay:", Vector2{ textX, textY }, Vector2{ 0, 0 }, 0, 30, 0, WHITE);
		DrawTextPro(font, "Avoid obstacles and survive as long as possible.",
			Vector2{ textX + 20, textY + spacing }, Vector2{ 0, 0 }, 0, 20, 0, WHITE);

		DrawTextPro(font, "Controls:", Vector2{ textX, textY + 2 * spacing }, Vector2{ 0, 0 }, 0, 30, 0, WHITE);
		DrawTextPro(font, "Single-player: Press SPACE to jump.",
			Vector2{ textX + 20, textY + 3 * spacing }, Vector2{ 0, 0 }, 0, 20, 0, WHITE);
		DrawTextPro(font, "Two-player: Player One jumps with W, Player Two with UP arrow.",
			Vector2{ textX + 20, textY + 4 * spacing }, Vector2{ 0, 0 }, 0, 20, 0, WHITE);

		DrawTextPro(font, "Difficulty Increase:", Vector2{ textX, textY + 5 * spacing }, Vector2{ 0, 0 }, 0, 30, 0, WHITE);
		DrawTextPro(font, "Every Three obstacles passed, the difficulty increases:",
			Vector2{ textX + 20, textY + 6 * spacing }, Vector2{ 0, 0 }, 0, 20, 0, WHITE);
		DrawTextPro(font, "ONE. Obstacle speed increases by TEN Percent.",
			Vector2{ textX + 20, textY + 7 * spacing }, Vector2{ 0, 0 }, 0, 20, 0, WHITE);
		DrawTextPro(font, "TWO. Spacing between obstacles decreases by TEN Percent.",
			Vector2{ textX + 20, textY + 8 * spacing }, Vector2{ 0, 0 }, 0, 20, 0, WHITE);
		DrawTextPro(font, "THREE. Spawn rate of obstacles increases by TEN Percent.",
			Vector2{ textX + 20, textY + 9 * spacing }, Vector2{ 0, 0 }, 0, 20, 0, WHITE);

		BUTTON::drawButton(button, font);
	}

}
