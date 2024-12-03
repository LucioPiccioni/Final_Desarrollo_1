#pragma once

#include <string>

#include "raylib.h"

#include "Engine/state_machine.cpp"

namespace BUTTON
{
	struct Button
	{
		std::string text;

		Rectangle rect = { 0,0,0,0 };

		GAME_STATES::Gamestate option = GAME_STATES::Gamestate::NONE;

		Color color = { 255, 182, 193, 255 };
		Color outline = { 1, 1, 1, 255 };
	};

	const float buttonWidth = 200;
	const float buttonHeight = 60;
	const float buttonSpacing = 20;

	const float titlesFontSize = 100;
	const float textFontSize = 40;
	const float scoreFontSize = 30;

	void drawButton(Button button, Font font);
	bool isButtonClicked(Vector2 mouse, Button button);
}



