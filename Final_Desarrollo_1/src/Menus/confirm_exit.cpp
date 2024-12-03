#include "confirm_exit.h"

#include "sounds.h"
#include "button.h"
#include "sprites.h"

namespace CONFIRM_EXIT
{
	const int maxButtons = 2;
	BUTTON::Button button[maxButtons];
	Vector2 mouse;

	void CONFIRM_EXIT::initButtons()
	{
		float startX;
		float startY;

		startX = (SCREEN_WIDTH - BUTTON::buttonWidth) / 2;
		startY = (SCREEN_HEIGHT - (BUTTON::buttonHeight * maxButtons + BUTTON::buttonSpacing * (maxButtons - 1))) / 2;

		button[0].option = GAME_STATES::Gamestate::CONFIRM_EXIT;
		button[1].option = GAME_STATES::Gamestate::CANCEL_EXIT;

		button[0].text = "Leave";
		button[1].text = "Stay";

		for (int i = 0; i < maxButtons; i++)
		{
			button[i].rect = { static_cast<float>(startX), static_cast<float>(startY + i * (BUTTON::buttonHeight + BUTTON::buttonSpacing)), BUTTON::buttonWidth, BUTTON::buttonHeight };

			switch (button[i].option)
			{
			case GAME_STATES::Gamestate::CONFIRM_EXIT:
				button[i].color = RED;
				break;

			case GAME_STATES::Gamestate::CANCEL_EXIT:
				button[i].color = GREEN;
				break;

			default:
				break;
			}
		}
	}

	void update(GAME_STATES::ProgramState& gameState)
	{
		mouse = GetMousePosition();

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
					StopSound(SOUNDS::gameSounds.button);
					PlaySound(SOUNDS::gameSounds.button);
					gameState.actual = button[i].option;
				}
			}
			else
			{
				button[i].color = { 255, 182, 193, 255 };
			}
		}

		switch (gameState.actual)
		{
		case GAME_STATES::Gamestate::CONFIRM_EXIT:

			gameState.actual = GAME_STATES::Gamestate::EXIT;
			break;

		case GAME_STATES::Gamestate::CANCEL_EXIT:

			gameState.actual = gameState.previusHud;
			//timmerToCleanBuffer = 0.01f;
			break;

		default:
			break;
		}
	}

	void draw(Font font)
	{
		SPRITES::drawBackgroundAssets();

		DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{ 0, 0, 0, 225 });

		DrawTextEx(font, "Are you sure you want to exit?",
			Vector2{ static_cast<float>(SCREEN_WIDTH) / 2 - MeasureTextEx(font, "Are you sure you want to exit?", BUTTON::textFontSize, 0).x / 2, static_cast<float>(SCREEN_HEIGHT / 4) },
			BUTTON::textFontSize, 0, RED);

		for (int i = 0; i < maxButtons; i++)
		{
			BUTTON::drawButton(button[i], font);
		}
	}
}
