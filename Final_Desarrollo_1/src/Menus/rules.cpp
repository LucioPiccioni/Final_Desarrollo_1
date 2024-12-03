#include "rules.h"

#include "raylib.h"

#include "Engine/game_data.h"
#include "Menus/button.h"
#include "Engine/sounds.h"
#include "Gameplay/sprites.h"

namespace RULES_MENU
{
	BUTTON::Button button;

	void initializeRulesMenu()
	{
		button.text = "Menu";

		button.rect = { (SCREEN_WIDTH - BUTTON::buttonWidth) * 0.5f ,
			SCREEN_HEIGHT - BUTTON::buttonHeight, BUTTON::buttonWidth,  BUTTON::buttonHeight };

		button.option = GAME_STATES::Gamestate::MAIN_MENU;
	}

	void updateRulesMenu(GAME_STATES::Gamestate& programState)
	{
		Vector2 mouse = GetMousePosition();

		SPRITES::updateTexturesPos(GetFrameTime());

		if (BUTTON::isButtonClicked(mouse, button))
		{
			button.color = WHITE;

			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				button.color = YELLOW;
			}

			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				StopSound(SOUNDS::gameSounds.button);
				PlaySound(SOUNDS::gameSounds.button);
				programState = GAME_STATES::Gamestate::MAIN_MENU;
			}
		}
		else
		{
			button.color = { 255, 182, 193, 255 };
		}
	}

	void drawRulesMenu(Font font)
	{
		SPRITES::drawBackgroundAssets();

		DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{ 0, 0, 0, 225 });

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
