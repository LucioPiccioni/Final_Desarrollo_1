#pragma once

#include <string>

#include "raylib.h"

#include "Program/program_Manager.h"

namespace BUTTON
{
	const Color button_Default_Color = { 255, 182, 193, 255 };
	const Color button_Outline_Color = { 1, 1, 1, 255 };

	struct Button
	{
		std::string text;

		Rectangle rect = { 0,0,0,0 };

		PROGRAM_MANAGER::Program_State option = PROGRAM_MANAGER::Program_State::NONE;

		Color color = button_Default_Color;
		Color outline = button_Outline_Color;
	};

	const float width = 200;
	const float height = 60;
	const float spacing = 20;

	const float titlesFontSize = 100;
	const float textFontSize = 40;
	const float scoreFontSize = 30;

	void drawButton(Button button, Font font);
	bool isButtonClicked(Vector2 mouse, Button button);
}



