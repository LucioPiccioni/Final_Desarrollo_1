#pragma once

#include "raylib.h"

#include "platform.h"

namespace PLAYER
{
	struct Player
	{
		int points_Record = 0;
		int points = 0;

		Vector2 pos = {};
		Vector2 speed = {};

		Rectangle frameRect = {};
		float currentFrame = 0;
		float framesCounter = 0;

		PLATFORM::Platform* platform_Standing;

		const float width = 32;
		const float height = 32;

		bool input_Pressed = false;
		bool on_Floor = false;
		bool animate = false;
	};

	extern Player player;

	const float jump_Force = -550;

	const float min_Gravity = 450;
	extern float actual_Gravity;
	const float max_Gravity = 500;
	

	const float friction = 30;
	const float movement_Speed = 250;

	void update(float delta_Time);

	void update_Movement(float delta_Time);

	void animate(float deltaTime);

	void movement_Input(float delta_Time);

	void apply_Gravity(float delta_Time);

	void apply_Friction(float delta_Time);

	void fix_Vertical_Speed_On_Platform();

	void update_Horizontal_Pos_On_Platform(float delta_Time);

	void limit_Horizontal_Speed();

	bool Is_on_Platform(Rectangle platform);

	bool collide_Width_Star(Rectangle star);

	void draw();
}
