#include "raylib.h"

#include "Engine/state_machine.h"

namespace CREDITS_MENU
{
	struct Credit
	{
		const char* text;
		const char* url;
		Rectangle buttonRect;
	};

	void initializeCreditsMenu();

	void updateCreditsMenu(GAME_STATES::Gamestate& programState);

	void drawCreditButton(Rectangle rect, const char* text, Font font, Color color, Color outline, float fontSize);

	void drawCreditsMenu(Font font);
}