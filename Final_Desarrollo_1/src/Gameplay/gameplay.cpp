#include "gameplay.h"

#include <string>

#include "Program/program_Manager.h"
#include "Program/program_Data.h"
#include "Program/Utilities/button.h"

#include "Res/sprites.h"
#include "Entities/player.h"
#include "Entities/platform.h"

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

	bool should_Increase_Difficulty()
	{
		return (PLAYER::player.points % 5 == 0 && PLAYER::player.points != 0);
	}

	void If_On_Platform(float delta_Time)
	{
		delta_Time = delta_Time;

		for (int i = 0; i < maxPlatform; i++)
		{
			if (PLAYER::player.speed.y >= 0 && PLAYER::Is_on_Platform(platform[i].rect_Pos))
			{
				PLAYER::player.on_Floor = true;

				if (!PLAYER::player.platform_Standing)
				{
					PLAYER::player.platform_Standing = &platform[i];
					PLAYER::player.pos.y = PLAYER::player.platform_Standing->rect_Pos.y - PLAYER::player.height + 0.5f;
				}

				PLAYER::fix_Vertical_Speed_On_Platform();

				update_Player_Points(platform[i]);


				break;
			}
			else
			{
				PLAYER::player.on_Floor = false;
				PLAYER::player.platform_Standing = nullptr;
			}
		}
	}

	bool did_Player_Died()
	{
		return (PLAYER::player.pos.y > PROGRAM_DATA::screenHeight);
	}

	void deactivate_Platform()
	{
		for (int i = 0; i < maxPlatform; i++)
		{
			if (platform[i].active && platform[i].rect_Pos.y > PROGRAM_DATA::screenHeight)
			{
				platform[i].active = false;
				break;
			}

		}
	}

	void update_Player_Points(PLATFORM::Platform& plat)
	{
		if (!plat.counted_Point)
		{
			PLAYER::player.points++;
			plat.counted_Point = true;

			if (should_Increase_Difficulty())
			{
				PLATFORM::speed_y *= diculty_Multiplier;

				PLATFORM::actual_length *= (0.95f);

				PLAYER::actual_Gravity *= diculty_Multiplier;

				if (PLATFORM::speed_y > PLATFORM::speed_y)
					PLATFORM::speed_y = PLATFORM::max_Speed.y;

				if (PLAYER::actual_Gravity > PLAYER::max_Gravity)
					PLAYER::actual_Gravity = PLAYER::max_Gravity;

				if (PLATFORM::actual_length < PLATFORM::min_length)
					PLATFORM::actual_length = PLATFORM::min_length;
			}
		}
	}
}
