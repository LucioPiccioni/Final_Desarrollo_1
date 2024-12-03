#pragma once

#include "raylib.h"

#include "program_Manager.h"

#include "platform.h"

namespace GAMEPLAY
{
	void init();

	void reset();

	void update(PROGRAM_MANAGER::State_Manager& state_manager);

	bool should_Increase_Difficulty();

	void If_On_Platform(float delta_Time);

	bool did_Player_Died();

	void activate_New_Platform();

	void deactivate_Platform();

	void draw(Font font);

	void update_Player_Points(PLATFORM::Platform& plat);
}