#pragma once

#include "raylib.h"

#include "Programs/program_Manager.h"

namespace MAIN_MENU
{
	void initializeMenu();

	void update(PROGRAM_MANAGER::State_Manager& state_manager, float delta_Time);

	void init();

	void draw(Font font);
}

