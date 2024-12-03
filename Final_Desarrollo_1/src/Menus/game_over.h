#pragma once

#include "raylib.h"

#include "Program/program_Manager.h"

namespace GAME_OVER
{
	void init();

	void update(PROGRAM_MANAGER::State_Manager& state_Manager);

	void draw(Font font);
}