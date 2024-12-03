#include "game_over.h"

#include "gameplay.h"
#include "gameplay2p.h"
#include "obstacle.h"

#include "sounds.h"
#include "button.h"
#include "game_data.h"

namespace GAME_OVER
{
	const int maxButtons = 3;
	Vector2 mouse;
	BUTTON::Button buttons[maxButtons] = {};

	void initButtons()
	{
		float startX = (static_cast<float>(SCREEN_WIDTH) - BUTTON::buttonWidth) / 2;
		float startY = ((static_cast<float>(SCREEN_HEIGHT) - SCREEN_HEIGHT / 5) - (BUTTON::buttonHeight * maxButtons + BUTTON::buttonSpacing * (maxButtons - 1)));

		for (int i = 0; i < maxButtons; i++)
		{
			buttons[i].rect = { startX, startY + i * (BUTTON::buttonHeight + BUTTON::buttonSpacing), BUTTON::buttonWidth, BUTTON::buttonHeight };
		}

		buttons[0].option = GAME_STATES::Gamestate::REPLAY;
		buttons[1].option = GAME_STATES::Gamestate::MAIN_MENU;
		buttons[2].option = GAME_STATES::Gamestate::WANT_TO_EXIT;

		buttons[0].text = "REPLAY";
		buttons[1].text = "MENU";
		buttons[2].text = "EXIT";
	}

	void update(GAME_STATES::ProgramState& gameState)
	{
		float deltaTime = GetFrameTime();

		mouse = GetMousePosition();

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


		if (OBSTACLE::actualSpeed > 0)
		{
			SPRITES::updateTexturesPos(deltaTime);
			OBSTACLE::actualSpeed -= 20 * deltaTime;
		}
		else if (OBSTACLE::actualSpeed < 0)
			OBSTACLE::actualSpeed = 0;


		if (gameState.actual == GAME_STATES::Gamestate::REPLAY)
		{
			if (gameState.previusGameMode == GAME_STATES::Gamestate::ONE_PLAYER_MODE)
				GAMEPLAY_1P::initializeGame();
			else
				GAMEPLAY_2P::initializeGame();

			gameState.actual = gameState.previusGameMode;
		}
		else if (gameState.actual == GAME_STATES::Gamestate::MAIN_MENU)
		{
			GAMEPLAY_1P::initializeGame();
			GAMEPLAY_2P::initializeGame();
		}
	}

	void draw(Font font)
	{
		Vector2 gameOverTextSize = MeasureTextEx(font, "GAME OVER", BUTTON::titlesFontSize, 0);
		Vector2 gameOverPos = { (static_cast<float>(SCREEN_WIDTH) - gameOverTextSize.x) * 0.5f, gameOverTextSize.y };

		SPRITES::drawBackgroundAssets();

		DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Color{ 0, 0, 0, 125 });

		DrawTextEx(font, "GAME OVER", gameOverPos, BUTTON::titlesFontSize, 0, RED);

		for (int i = 0; i < maxButtons; i++)
		{
			BUTTON::drawButton(buttons[i], font);
		}
	}
}

