#include "pause.h"

#include "Engine/sounds.h"
#include "Engine/game_data.h"
#include "GamePlay/gameplay.h"
#include "Menus/button.h"
#include "Gameplay/gameplay2p.h"

namespace PAUSE
{
	const int buttonCount = 3;
	Vector2 mouse;
	BUTTON::Button buttons[buttonCount] = {};

	void initButtons()
	{
		float startX = (SCREEN_WIDTH - BUTTON::buttonWidth) / 2;
		float startY = SCREEN_HEIGHT - (BUTTON::buttonHeight * buttonCount + BUTTON::buttonSpacing * (buttonCount - 1));


		buttons[0].option = GAME_STATES::Gamestate::ONE_PLAYER_MODE;
		buttons[1].option = GAME_STATES::Gamestate::MAIN_MENU;
		buttons[2].option = GAME_STATES::Gamestate::WANT_TO_EXIT;

		buttons[0].text = "RESUME";
		buttons[1].text = "MENU";
		buttons[2].text = "EXIT";

		Color outline = BLACK;

		for (int i = 0; i < buttonCount; i++)
		{
			buttons[i].rect = { startX, startY + i * (BUTTON::buttonHeight + BUTTON::buttonSpacing), BUTTON::buttonWidth, BUTTON::buttonHeight };
			buttons[i].outline = outline;
		}

	}

	void update(GAME_STATES::ProgramState& gameState)
	{
		mouse = GetMousePosition();

		if (IsKeyPressed(KEY_ESCAPE))
			gameState.actual = gameState.previusGameMode;

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

		if (gameState.actual == GAME_STATES::Gamestate::MAIN_MENU)
		{
			if (gameState.previusGameMode == GAME_STATES::Gamestate::ONE_PLAYER_MODE)
				GAMEPLAY_1P::initializeGame();
			else
				GAMEPLAY_2P::initializeGame();
		}
	}

	void draw(Font font, GAME_STATES::Gamestate previusGameMode)
	{
		Vector2 titlePos =
		{
			(SCREEN_WIDTH) / 2 - MeasureTextEx(font, "Pause", BUTTON::titlesFontSize, 2).x / 2,
			(SCREEN_HEIGHT) / 5
		};

		Color pastelPurple = { 214, 196, 224, 255 };

		if (previusGameMode == GAME_STATES::Gamestate::ONE_PLAYER_MODE)
			GAMEPLAY_1P::drawGame();
		else
			GAMEPLAY_2P::drawGame();

		DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{ 0, 0, 0, 125 });

		DrawTextEx(font, "Pause", titlePos, BUTTON::titlesFontSize, 2, pastelPurple);

		for (int i = 0; i < buttonCount; i++)
		{
			BUTTON::drawButton(buttons[i], font);
		}
	}
}

