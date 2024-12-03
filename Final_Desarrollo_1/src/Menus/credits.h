#include "raylib.h"

#include "Program/program_Manager.h"

namespace CREDITS
{
	struct Credit
	{
		const char* text;
		const char* url;
		Rectangle buttonRect;
	};

	void init();

	void update(PROGRAM_MANAGER::Program_State& program_State);

	void drawCreditButton(Rectangle rect, const char* text, Font font, Color color, Color outline, float fontSize);

	void draw(Font font);
}