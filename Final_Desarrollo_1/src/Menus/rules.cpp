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

		button.rect = { ( PROGRAM_DATA::screen_Width - BUTTON::width) * 0.5f ,
			PROGRAM_DATA::screen_Height - BUTTON::height * 2, BUTTON::width,  BUTTON::height };

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
			static_cast<int>(PROGRAM_DATA::screen_Width),
			static_cast<int>(PROGRAM_DATA::screen_Height), Color{ 0, 0, 0, 225 });

		DrawTextPro(font, "Rules",
			Vector2{ (GetScreenWidth() - MeasureTextEx(font, "Rules", 40, 0).x) * 0.5f, 50 },
			Vector2{ 0, 0 }, 0, 40, 0, WHITE);

		float textX = 50;
		float textY = 150;
		float spacing = 40;

		DrawTextPro(font, "Gameplay:", Vector2{ textX, textY }, Vector2{ 0, 0 }, 0, 30, 0, WHITE);
		DrawTextPro(font, "Jump through platforms and survive as long as possible.",
			Vector2{ textX + 20, textY + spacing }, Vector2{ 0, 0 }, 0, 20, 0, WHITE);

		DrawTextPro(font, "Controls:", Vector2{ textX, textY + 3 * spacing }, Vector2{ 0, 0 }, 0, 30, 0, WHITE);
		DrawTextPro(font, "SPACE / W / Up Arrow: To jump.",
			Vector2{ textX + 20, textY + 4 * spacing }, Vector2{ 0, 0 }, 0, 20, 0, WHITE);
		DrawTextPro(font, "A / Left Arrow: To move to Left.",
			Vector2{ textX + 20, textY + 5 * spacing }, Vector2{ 0, 0 }, 0, 20, 0, WHITE);
		DrawTextPro(font, "D / Right Arrow: To move to Right.",
			Vector2{ textX + 20, textY + 6 * spacing }, Vector2{ 0, 0 }, 0, 20, 0, WHITE);

		DrawTextPro(font, "Difficulty Increase:", Vector2{ textX, textY + 8 * spacing }, Vector2{ 0, 0 }, 0, 30, 0, WHITE);
		DrawTextPro(font, "Every Five points, the difficulty increases:",
			Vector2{ textX + 20, textY + 9 * spacing }, Vector2{ 0, 0 }, 0, 20, 0, WHITE);
		DrawTextPro(font, "* Platform speed increases by 15 %.",
			Vector2{ textX + 20, textY + 10 * spacing }, Vector2{ 0, 0 }, 0, 20, 0, WHITE);
		DrawTextPro(font, "* Gravity force is increases by 15 %.",
			Vector2{ textX + 20, textY + 11 * spacing }, Vector2{ 0, 0 }, 0, 20, 0, WHITE);
		DrawTextPro(font, "* The Spacing of the platforms decreases by 5 %.",
			Vector2{ textX + 20, textY + 12 * spacing }, Vector2{ 0, 0 }, 0, 20, 0, WHITE);

		BUTTON::drawButton(button, font);
	}

}
