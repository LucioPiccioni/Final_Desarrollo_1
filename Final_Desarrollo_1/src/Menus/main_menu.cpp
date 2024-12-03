#include "main_menu.h"

#include "Engine/sounds.h"
#include "Engine/music.h"
#include "Menus/button.h"
#include "Engine/game_data.h"
#include "Gameplay/sprites.h"

namespace MAIN_MENU
{
	static const int maxButtons = 5;
	static BUTTON::Button buttons[maxButtons];
	Texture2D gamesTitle;

	void initializeMenu()
	{
		SPRITES::spritesMovement = { 0,0,0,0 };
		initializeButtons();
	}

	void updateMenu(GAME_STATES::ProgramState& gameState)
	{
		Vector2 mouse = GetMousePosition();

		if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT)) && SOUND_TRACKS::volume > 0)
			SOUND_TRACKS::volume -= 0.01f;
		else if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_RIGHT)) && SOUND_TRACKS::volume < 1)
			SOUND_TRACKS::volume += 0.01f;

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
					StopSound(SOUNDS::gameSounds.button);
					PlaySound(SOUNDS::gameSounds.button);
					gameState.actual = buttons[i].option;
				}
			}
			else
			{
				buttons[i].color = { 255, 182, 193, 255 };
			}
		}

		SPRITES::updateTexturesPos(GetFrameTime());
	}

	void drawMenu(Font font)
	{
		SPRITES::drawBackgroundAssets();

		DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{ 0, 0, 0, 125 });

		DrawText("v0.5", 0, 0, 20, WHITE);

		DrawTextPro(font,
			"The Spark",
			Vector2{ (SCREEN_WIDTH - MeasureTextEx(font, "The Spark", BUTTON::titlesFontSize, 0).x) * 0.5f,
					 MeasureTextEx(font, "The Spark", BUTTON::titlesFontSize, 0).y * 0.5f },
			Vector2{ 0, 0 },
			0, BUTTON::titlesFontSize,
			0,
			YELLOW);

		for (int i = 0; i < maxButtons; i++)
		{
			BUTTON::drawButton(buttons[i], font);
		}

		DrawText("Hold Left/Down to lower volume,", 10, SCREEN_HEIGHT - 60, 14, WHITE);
		DrawText("Right/Up to increase volume", 10, SCREEN_HEIGHT - 40, 14, WHITE);

		int volumePercentage = static_cast<int>(SOUND_TRACKS::volume * 100);
		DrawText(("Volume: " + std::to_string(volumePercentage) + "%").c_str(), 10, SCREEN_HEIGHT - 20, 14, WHITE);
	}


	void initializeButtons()
	{
		float startX = (SCREEN_WIDTH - BUTTON::buttonWidth) / 2;
		float startY = SCREEN_HEIGHT - (BUTTON::buttonHeight * maxButtons + BUTTON::buttonSpacing * (maxButtons - 1));

		for (int i = 0; i < maxButtons; i++)
		{
			buttons[i].rect = { startX, startY + i * (BUTTON::buttonHeight + BUTTON::buttonSpacing), BUTTON::buttonWidth, BUTTON::buttonHeight };
			buttons[i].color = BLACK;
		}

		buttons[0].option = GAME_STATES::Gamestate::ONE_PLAYER_MODE;
		buttons[1].option = GAME_STATES::Gamestate::TWO_PLAYER_MODE;
		buttons[2].option = GAME_STATES::Gamestate::RULES;
		buttons[3].option = GAME_STATES::Gamestate::CREDITS;
		buttons[4].option = GAME_STATES::Gamestate::WANT_TO_EXIT;

		buttons[0].text = "Solo MODE";
		buttons[1].text = "Coop MODE";
		buttons[2].text = "RULES";
		buttons[3].text = "CREDITS";
		buttons[4].text = "EXIT";

	}

}

