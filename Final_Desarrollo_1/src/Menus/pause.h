#pragma once

#include "raylib.h"

#include "Gameplay/gameplay.h"
#include "Program/program_Manager.h"

namespace PAUSE
{
	void init();

	void update(PROGRAM_MANAGER::State_Manager& state_Manager);

	void draw(Font font);
}