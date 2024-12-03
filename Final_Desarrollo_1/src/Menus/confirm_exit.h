#include "raylib.h"

#include "Engine/state_machine.h"
#include "Engine/game_data.h"

namespace CONFIRM_EXIT
{
	void initButtons();

	void update(GAME_STATES::ProgramState& gameState);

	void draw(Font font);
}