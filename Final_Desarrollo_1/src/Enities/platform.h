#pragma once

#include "raylib.h"

namespace PLATFORM
{
	struct Platform
	{
		Rectangle rect_Pos = {};
		Rectangle rectDest = {};

		Vector2 speed = {};

		bool moves_In_x = false;

		bool right_Movement = false;
		bool left_Movement = false;

		bool active = false;

		bool counted_Point = false;
	};

	const Vector2 min_Speed = { 10, 100 };
	extern float speed_y;
	const Vector2 max_Speed = { 200, 200 };

	const float max_length = 240;
	extern float actual_length;
	const float min_length = 100;

	Platform spawner();

	void update(Platform& platform, float delta_Time);

	void move(Platform& platform, float delta_Time);

	void changeDirectionX(Platform& platform);

	void draw(Rectangle rect);
}