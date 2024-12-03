#pragma once

#include "raylib.h"

#include "Gameplay/gameplay.h"
#include "Engine/state_machine.h"

namespace PAUSE
{
	void initButtons();

	void update(GAME_STATES::ProgramState& gameState);

	void draw(Font font, GAME_STATES::Gamestate previusGameMode);
}