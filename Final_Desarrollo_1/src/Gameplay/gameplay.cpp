#include "gameplay.h"

#include <string>

#include "Program/program_Manager.h"
#include "Program/program_Data.h"
#include "Program/Utilities/button.h"

#include "Res/sprites.h"
#include "Entites/player.h"
#include "Entites/platform.h"

namespace GAMEPLAY
{
	const int maxPlatform = 5;

	const float diculty_Multiplier = 1.15f;

	int lastActiveIndex = 0;

	PLATFORM::Platform platform[maxPlatform];

	void init()
	{
		reset();
	}

	void reset()
	{
		for (int i = 0; i < maxPlatform; i++)
		{
			platform[i].active = false;
			PLATFORM::speed_y = PLATFORM::min_Speed.y;
		}

		PLAYER::player.points = 0;

		lastActiveIndex = 0;

		platform[0] = PLATFORM::spawner();

		platform[0].rect_Pos.x = (PROGRAM_DATA::screenWidth - platform[0].rect_Pos.width) * 0.5f;
		platform[0].rect_Pos.y = PROGRAM_DATA::screenHeight - PLAYER::player.height - 600;

		PLAYER::player.pos = { (PROGRAM_DATA::screenWidth - PLAYER::player.width) * 0.5f,
						platform[0].rect_Pos.y - PLAYER::player.height };

		PLAYER::player.platform_Standing = nullptr;

		PLAYER::player.speed = { 0,0 };

		PLATFORM::speed_y = PLATFORM::min_Speed.y;
		PLATFORM::actual_length = PLATFORM::max_length;
	}

	void update(PROGRAM_MANAGER::State_Manager& state_Manager)
	{
		float delta_Time = GetFrameTime();

		SPRITE::update_Paralax_Pos(delta_Time);

		if (IsKeyPressed(KEY_ESCAPE))
		{
			state_Manager.previus = PROGRAM_MANAGER::Program_State::GAMEPLAY;
			state_Manager.actual = PROGRAM_MANAGER::Program_State::PAUSE;
		}

		If_On_Platform(delta_Time);

		PLAYER::update(delta_Time);

		for (int i = 0; i < maxPlatform; i++)
		{
			PLATFORM::update(platform[i], delta_Time);
		}

		activate_New_Platform();

		deactivate_Platform();

		if (did_Player_Died())
		{
			init();
			state_Manager.actual = PROGRAM_MANAGER::Program_State::GAME_OVER;
		}
	}
}
