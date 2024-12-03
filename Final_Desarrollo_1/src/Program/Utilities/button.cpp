#include "button.h"

#include <string>

namespace BUTTON
{
	void drawButton(Button button, Font font)
	{
		DrawRectangleRec(button.rect, button.color);
		DrawRectangleLinesEx(button.rect, 2, button.outline);

		Vector2 textSize = MeasureTextEx(font, button.text.c_str(), textFontSize, 1);

		Vector2 textPosition = {
			button.rect.x + (button.rect.width - textSize.x) / 2,
			button.rect.y + (button.rect.height - textSize.y) / 2
		};

		DrawTextPro(font,
			button.text.c_str(),
			textPosition,
			Vector2{ 0,0 },
			0,
			textFontSize,
			0,
			BLACK);
	}

	bool isButtonClicked(Vector2 mouse, Button button)
	{
		return (mouse.x >= button.rect.x &&
			mouse.x <= button.rect.x + button.rect.width &&
			mouse.y >= button.rect.y &&
			mouse.y <= button.rect.y + button.rect.height);
	}
}