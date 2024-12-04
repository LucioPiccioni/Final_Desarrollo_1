#include "credits.h"

#include "raylib.h"

#include "Program/program_Data.h"
#include "Program/Utilities/button.h"

#include "Res/sounds.h"
#include "Res/sprites.h"

namespace CREDITS
{
	const int maxCredits = 9;

	BUTTON::Button button = {};

	Credit credits[maxCredits] =
	{
		{"", "https://kapnack.itch.io", {}},
		{"Pixel Frog \"Virtual Boy\" - Character.", "https://pixelfrog-assets.itch.io/pixel-adventure-1", {}},
		{"Plrang Art \"Iron stone meteorite or coal surface\" - Platform.", "http://spritefx.blogspot.com/2013/04/sprite-wind.html", {}},
		{"DinVStudio \"Dynamic space background\" - Paralax.", "https://dinvstudio.itch.io/dynamic-space-background-lite-free", {}},
		{"Chiptone \"Sound Effects\".", "https://sfbgames.itch.io/chiptone", {}},
		{"Purrple Cat \"Breathtaking\" - Gameplay music.", "https://www.youtube.com/watch?v=wvJgGh1EpaU", {}},
		{"Harris Cole \"Louie's Lullaby\" - Credits Music.", "https://www.youtube.com/watch?v=lraoB66OW1s", {}},
		{"Jen \"Quiet Nights\" - Game Over music.", "https://www.youtube.com/watch?v=d_-ECIjWTHY", {}},
		{"The Fontry \"JSL Space Gothic\" - Font.", "https://thefontry.com/jlsdatagothic/", {}}
	};

	void init()
	{
		float buttonURLWidth = 120;
		float buttonURLHeight = 30;
		float buttonURLspacing = 20;

		float startX = PROGRAM_DATA::screen_Width - buttonURLWidth * 1.5f;
		float startY = 150;

		for (int i = 0; i < maxCredits; i++)
		{
			credits[i].buttonRect = { startX, startY + i * (buttonURLHeight + buttonURLspacing), buttonURLWidth, buttonURLHeight };
		}

		button.rect = {
			(PROGRAM_DATA::screen_Width - BUTTON::width) * 0.5f,
			PROGRAM_DATA::screen_Height - BUTTON::height * 2,
			BUTTON::width,
			BUTTON::height };

		button.text = "Menu";
	}

	void update(PROGRAM_MANAGER::Program_State& program_State)
	{
		Vector2 mouse = GetMousePosition();

		SPRITE::update_Paralax_Pos(GetFrameTime());

		for (int i = 0; i < maxCredits; i++)
		{
			if (CheckCollisionPointRec(mouse, credits[i].buttonRect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				StopSound(SOUND::gameSounds.button);
				PlaySound(SOUND::gameSounds.button);
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
				StopSound(SOUND::gameSounds.button);
				PlaySound(SOUND::gameSounds.button);
				program_State = PROGRAM_MANAGER::Program_State::MAIN_MENU;
			}
		}
		else
		{
			button.color = BUTTON::button_Default_Color;
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


	void draw(Font font)
	{
		SPRITE::draw_Paralax();

		DrawRectangle(0, 0, 
			static_cast<int>(PROGRAM_DATA::screen_Width), 
			static_cast<int>(PROGRAM_DATA::screen_Height), 
			Color{ 0, 0, 0, 125 });

		DrawTextPro(font, "Developed by: Lucio Piccioni",
			Vector2{ (PROGRAM_DATA::screen_Width - MeasureTextEx(font, "Developed by: Lucio Piccioni", BUTTON::textFontSize, 0).x) * 0.5f,
			MeasureTextEx(font, "Developed by: Lucio Piccioni", BUTTON::textFontSize, 0).y },
			Vector2{ 0, 0 },
			0,
			BUTTON::textFontSize,
			0,
			WHITE);

		Vector2 myButton =
			Vector2{ (PROGRAM_DATA::screen_Width - BUTTON::width) * 0.5f,
			MeasureTextEx(font, "Developed by: Lucio Piccioni", BUTTON::textFontSize, 0).y * 2 };

		float startX = 100;
		float startY = 150;
		float spacing = 20;

		credits[0].buttonRect = Rectangle{ myButton.x, myButton.y, BUTTON::width, BUTTON::height };

		for (int i = 0; i < maxCredits; i++)
		{
			DrawTextPro(font, credits[i].text,
				Vector2{ startX, startY + i * (30 + spacing) },
				Vector2{ 0, 0 }, 0, BUTTON::textFontSize * 0.5f,
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
