#include "player.h"

#include "raylib.h"

#include "Program/program_Data.h"

#include "Res/sprites.h"
#include "Res/sounds.h"

namespace PLAYER
{
	Player player = {};

	float actual_Gravity = min_Gravity;

	void update(float delta_Time)
	{
		update_Movement(delta_Time);
	}

	void update_Movement(float delta_Time)
	{
		movement_Input(delta_Time);

		apply_Gravity(delta_Time);

		apply_Friction(delta_Time);

		animate(delta_Time);

		update_Horizontal_Pos_On_Platform(delta_Time);

		limit_Horizontal_Speed();

		player.pos.y += player.speed.y * delta_Time;
		player.pos.x += player.speed.x * delta_Time;

		if (player.speed.x > movement_Speed) player.speed.x = movement_Speed;
		if (player.speed.x < -movement_Speed) player.speed.x = -movement_Speed;

		if (player.pos.x > PROGRAM_DATA::screen_Width) player.pos.x = 0;
		if (player.pos.x + player.width < 0) player.pos.x = PROGRAM_DATA::screen_Width;

		if (player.speed.x > -1.0f && player.speed.x < 1.0f && !player.input_Pressed) player.speed.x = 0;
	}

	void animate(float deltaTime)
	{
		player.frames_Counter += deltaTime;

		const float frameDuration = 0.12f;

		if (player.frames_Counter >= frameDuration)
		{
			player.frames_Counter -= frameDuration;
			player.current_Frame++;

			if (player.current_Frame > SPRITE::animation_Total_Frames)
			{
				player.current_Frame = 0;
				player.animate = false;
			}

			player.frame_Rect.x = static_cast<float>(player.current_Frame) * (SPRITE::sprites.player_Run.width / SPRITE::animation_Total_Frames);
		}
	}

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
			StopSound(SOUND::game_Sounds.jump);
			PlaySound(SOUND::game_Sounds.jump);

			player.speed.y = jump_Force;
			player.on_Floor = false;
			player.platform_Standing = nullptr;
		}
	}

	void apply_Gravity(float delta_Time)
	{
		if (!player.on_Floor)
			player.speed.y += actual_Gravity * delta_Time;
	}

	void apply_Friction(float delta_Time)
	{
		if (player.speed.x != 0)
		{
			if (player.speed.x < 0)
				player.speed.x += friction * delta_Time;
			else
				player.speed.x -= friction * delta_Time;
		}
	}

	void fix_Vertical_Speed_On_Platform()
	{
		player.speed.y = PLATFORM::speed_y;
	}

	void update_Horizontal_Pos_On_Platform(float delta_Time)
	{
		delta_Time = delta_Time;

		if (player.platform_Standing)
		{
			float relative_X = player.pos.x - player.platform_Standing->rect_Pos.x;

			player.pos.x = player.platform_Standing->rect_Pos.x + relative_X;

			Rectangle platform_Bounds = {
				player.platform_Standing->rect_Pos.x,
				player.platform_Standing->rect_Pos.y,
				player.platform_Standing->rect_Pos.width,
				player.platform_Standing->rect_Pos.height
			};

			if (player.pos.x < platform_Bounds.x)
			{
				player.pos.x = platform_Bounds.x;
				player.speed.x = 0;

				if (player.speed.x < 0)
					player.speed.x += friction * delta_Time;
			}
			else if (player.pos.x + player.width > platform_Bounds.x + platform_Bounds.width)
			{
				player.pos.x = platform_Bounds.x + platform_Bounds.width - player.width;

				if (player.speed.x > 0)
					player.speed.x -= friction * delta_Time;
			}
		}
	}

	void limit_Horizontal_Speed()
	{
		if (player.speed.x > movement_Speed)
		{
			player.speed.x = movement_Speed;
		}
		if (player.speed.x < -movement_Speed)
		{
			player.speed.x = -movement_Speed;
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

	bool collide_Width_Star(Rectangle star) 
	{
		return (
			player.pos.x < star.x + star.width && 
			player.pos.x + player.width > star.x &&
			player.pos.y < star.y + star.height &&
			player.pos.y + player.height > star.y
			);
	}


	void draw()
	{
		Vector2 sprite_Ralted_Player_Pos;
		Texture2D current_Sprite;
		Rectangle source_Rect;
		Rectangle dest_Rect;
		Vector2 origin = { 0, 0 };
		float rotation = 0;

#ifdef _DEBUG
		DrawRectangleV(player.pos, Vector2{ player.width, player.height }, BLUE);
#endif

		if (!player.on_Floor)
		{
			source_Rect = { 0.0f, 0.0f, (player.speed.x > 0 ? 1 : -1) * static_cast<float>(SPRITE::sprites.player_Jump.width), static_cast<float>(SPRITE::sprites.player_Jump.height) };
			current_Sprite = SPRITE::sprites.player_Jump;
			sprite_Ralted_Player_Pos = { player.pos.x, player.pos.y };
			source_Rect.x = { static_cast<float>(player.current_Frame) * (SPRITE::sprites.player_Idle.width / SPRITE::animation_Total_Frames) };
		}
		else if (player.speed.x != 0)
		{
			// Animación de caminar
			current_Sprite = SPRITE::sprites.player_Run;
			source_Rect =
			{
				static_cast<float>(player.current_Frame) * (SPRITE::sprites.player_Run.width / (SPRITE::animation_Total_Frames + 1)),
				0.0f,
				(player.speed.x > 0 ? 1 : -1) * (static_cast<float>(SPRITE::sprites.player_Run.width) / (SPRITE::animation_Total_Frames + 1)),
				static_cast<float>(SPRITE::sprites.player_Run.height)
			};
			sprite_Ralted_Player_Pos = { player.pos.x, player.pos.y };
		}
		else
		{
			// Animación de Idle
			current_Sprite = SPRITE::sprites.player_Idle;
			source_Rect = {
				static_cast<float>(player.current_Frame) * (SPRITE::sprites.player_Idle.width / SPRITE::animation_Total_Frames),
				0.0f,
				static_cast<float>(SPRITE::sprites.player_Idle.width) / SPRITE::animation_Total_Frames,
				static_cast<float>(SPRITE::sprites.player_Idle.height)
			};
			sprite_Ralted_Player_Pos = { player.pos.x, player.pos.y };
		}


		dest_Rect = {
			sprite_Ralted_Player_Pos.x,
			sprite_Ralted_Player_Pos.y,
			player.width,
			player.height
		};

		DrawTexturePro(
			current_Sprite,
			source_Rect,
			dest_Rect,
			origin,
			rotation,
			WHITE
		);
	}
}
