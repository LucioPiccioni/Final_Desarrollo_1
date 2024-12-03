#include "player.h"

#include "raylib.h"

#include "Program/program_Data.h"
#include "Res/sprites.h"

namespace PLAYER
{
	Player player = {};

	float actual_Gravity = min_Gravity;

	void movement_Input(float delta_Time)
	{
		player.input_Pressed = false;

		if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
		{
			player.speed.x -= movement_Speed * delta_Time;
			player.input_Pressed = true;
		}

		if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
		{
			player.speed.x += movement_Speed * delta_Time;
			player.input_Pressed = true;
		}

		if ((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_SPACE)) && player.on_Floor)
		{
			player.speed.y = jump_Force;
			player.on_Floor = false;
			player.platform_Standing = nullptr;
		}
	}

	bool Is_on_Platform(Rectangle platform)
	{
		return (
			(player.pos.y + player.height >= platform.y) &&
			(player.pos.y + player.height <= platform.y + platform.height) &&
			(player.pos.x + player.width > platform.x) &&
			(player.pos.x < platform.x + platform.width));
	}
}
