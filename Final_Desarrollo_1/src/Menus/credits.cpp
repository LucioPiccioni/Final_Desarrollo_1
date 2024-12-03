#include "credits.h"

#include "raylib.h"

#include "Engine/game_data.h"
#include "Engine/sounds.h"
#include "Gameplay/sprites.h"
#include "Menus/button.h"

namespace CREDITS_MENU
{
	const int maxCredits = 8;

	BUTTON::Button button = {};

	Credit credits[maxCredits] =
	{
		{"", "https://kapnack.itch.io", {}},
		{"Cgman \"Wind VFX\"", "http://spritefx.blogspot.com/2013/04/sprite-wind.html", {}},
		{"Purrple Cat \"Breathtaking\"", "https://www.youtube.com/watch?v=wvJgGh1EpaU", {}},
		{"Harris Cole \"Louie's Lullaby\"", "https://www.youtube.com/watch?v=lraoB66OW1s", {}},
		{"Chiptone \"Sound Effects\"", "https://sfbgames.itch.io/chiptone", {}},
		{"Waters \"City Background Parallax\"", "https://waterscreate.itch.io/city-background-parallax", {}},
		{"Pixeleart \"Paper plane with pixel art style\"", "https://www.freepik.com/premium-vector/paper-plane-with-pixel-art-style_18019937.htm", {}},
		{"Jen \"Quiet Nights\"", "https://www.youtube.com/watch?v=d_-ECIjWTHY", {}}
	};

	void initializeCreditsMenu()
	{
		float startX = 100;
		float startY = 150;
		float buttonWidth = 120;
		float buttonHeight = 30;
		float spacing = 20;

		for (int i = 0; i < maxCredits; i++)
		{
			credits[i].buttonRect = { startX + 600, startY + i * (buttonHeight + spacing), buttonWidth, buttonHeight };
		}

		button.rect = { SCREEN_WIDTH * 0.5f - BUTTON::buttonWidth * 0.5f, SCREEN_HEIGHT - BUTTON::buttonHeight, BUTTON::buttonWidth, BUTTON::buttonHeight };
		button.text = "Menu";
	}

	void updateCreditsMenu(GAME_STATES::Gamestate& programState)
	{
		Vector2 mouse = GetMousePosition();

		SPRITES::updateTexturesPos(GetFrameTime());

		for (int i = 0; i < maxCredits; i++)
		{
			if (CheckCollisionPointRec(mouse, credits[i].buttonRect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				StopSound(SOUNDS::gameSounds.button);
				PlaySound(SOUNDS::gameSounds.button);
				OpenURL(credits[i].url);
			}
		}

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

	void drawCreditButton(Rectangle rect, const char* text, Font font, Color color, Color outline, float fontSize)
	{
		DrawRectangleRec(rect, color);
		DrawRectangleLinesEx(rect, 2, outline);

		Vector2 textSize = MeasureTextEx(font, text, fontSize, 1);

		Vector2 textPosition = {
			rect.x + (rect.width - textSize.x) / 2,
			rect.y + (rect.height - textSize.y) / 2
		};

		DrawTextPro(font,
			text,
			textPosition,
			Vector2{ 0, 0 },
			0,
			fontSize,
			1,
			BLACK);
	}


	void drawCreditsMenu(Font font)
	{
		SPRITES::drawBackgroundAssets();

		DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{ 0, 0, 0, 125 });

		DrawTextPro(font, "Developed by: Lucio Piccioni",
			Vector2{ (SCREEN_WIDTH - MeasureTextEx(font, "Developed by: Lucio Piccioni", BUTTON::textFontSize, 0).x) * 0.5f,
			MeasureTextEx(font, "Developed by: Lucio Piccioni", BUTTON::textFontSize, 0).y },
			Vector2{ 0, 0 },
			0,
			BUTTON::textFontSize,
			0,
			WHITE);

		Vector2 myButton =
			Vector2{ (SCREEN_WIDTH - BUTTON::buttonWidth) * 0.5f,
			MeasureTextEx(font, "Developed by: Lucio Piccioni", BUTTON::textFontSize, 0).y * 2 };

		float startX = 100;
		float startY = 150;
		float spacing = 20;

		credits[0].buttonRect = Rectangle{ myButton.x, myButton.y, BUTTON::buttonWidth, BUTTON::buttonHeight };

		for (int i = 0; i < maxCredits; i++)
		{
			DrawTextPro(font, credits[i].text, 
				Vector2{ startX, startY + i * (30 + spacing) }, 
				Vector2{ 0, 0 }, 0, BUTTON::textFontSize * 0.70,
				0, 
				WHITE);

			drawCreditButton(
				credits[i].buttonRect,
				"Link",
				font,
				PURPLE,
				WHITE,
				BUTTON::scoreFontSize
			);
		}

		BUTTON::drawButton(button, font);
	}
}
