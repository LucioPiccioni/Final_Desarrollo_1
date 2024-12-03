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

	void draw()
	{
		Vector2 spriteRaltedPlayerPos;
		Texture2D currentSprite;
		Rectangle sourceRect;
		Rectangle destRect;
		Vector2 origin = { 0, 0 };
		float rotation = 0;

#ifdef _DEBUG
		DrawRectangleV(player.pos, Vector2{ player.width, player.height }, GREEN);
#endif

		if (!player.on_Floor)
		{
			sourceRect = { 0.0f, 0.0f, (player.speed.x > 0 ? 1 : -1) * static_cast<float>(SPRITE::sprites.player_Jump.width), static_cast<float>(SPRITE::sprites.player_Jump.height) };
			currentSprite = SPRITE::sprites.player_Jump;
			spriteRaltedPlayerPos = { player.pos.x, player.pos.y };
			sourceRect.x = { static_cast<float>(player.currentFrame) * (SPRITE::sprites.player_Idle.width / SPRITE::animationTotalFrames) };
		}
		else if (player.speed.x != 0)
		{
			// Animaci�n de caminar
			currentSprite = SPRITE::sprites.player_Run;
			sourceRect =
			{
				static_cast<float>(player.currentFrame) * (SPRITE::sprites.player_Run.width / (SPRITE::animationTotalFrames + 1)),
				0.0f,
				(player.speed.x > 0 ? 1 : -1) * (static_cast<float>(SPRITE::sprites.player_Run.width) / (SPRITE::animationTotalFrames + 1)),
				static_cast<float>(SPRITE::sprites.player_Run.height)
			};
			spriteRaltedPlayerPos = { player.pos.x, player.pos.y };
		}
		else
		{
			// Animaci�n de Idle
			currentSprite = SPRITE::sprites.player_Idle;
			sourceRect = {
				static_cast<float>(player.currentFrame) * (SPRITE::sprites.player_Idle.width / SPRITE::animationTotalFrames),
				0.0f,
				static_cast<float>(SPRITE::sprites.player_Idle.width) / SPRITE::animationTotalFrames,
				static_cast<float>(SPRITE::sprites.player_Idle.height)
			};
			spriteRaltedPlayerPos = { player.pos.x, player.pos.y };
		}


		destRect = {
			spriteRaltedPlayerPos.x,
			spriteRaltedPlayerPos.y,
			player.width,
			player.height
		};

		DrawTexturePro(
			currentSprite,
			sourceRect,
			destRect,
			origin,
			rotation,
			WHITE
		);
	}
}
