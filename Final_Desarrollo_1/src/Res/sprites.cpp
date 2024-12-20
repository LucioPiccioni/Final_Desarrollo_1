#include "sprites.h"

#include "Program/program_Data.h"
#include "Entities/platform.h"

namespace SPRITE
{
	const int animation_Total_Frames = 11;

	Sprites sprites = {};
	SpriteMovement sprites_Movement = {};

	void init()
	{
		sprites.player_Idle = LoadTexture("res/Character/Idle (32x32).png");
		sprites.player_Run = LoadTexture("res/Character/Run (32x32).png");
		sprites.player_Jump = LoadTexture("res/Character/Jump (32x32).png");

		sprites.platform = LoadTexture("res/platform.png");
		sprites.star = LoadTexture("res/star.png");

		sprites.space = LoadTexture("res/Paralax/space.png");
	}

	void unload()
	{
		UnloadTexture(sprites.player_Idle);
		UnloadTexture(sprites.player_Run);
		UnloadTexture(sprites.player_Jump);

		UnloadTexture(sprites.platform);
		UnloadTexture(sprites.star);

		UnloadTexture(sprites.space);
	}

	void update_Paralax_Pos(float delta_Time)
	{
		float skySpeed = (PLATFORM::speed_y * 0.5f) * delta_Time;

		delta_Time = delta_Time + 2;

		if (skySpeed > 0)
			SPRITE::sprites_Movement.space -= skySpeed;

		if (SPRITE::sprites_Movement.space < -PROGRAM_DATA::screen_Height)
			SPRITE::sprites_Movement.space = 0;
	}

	void draw_Paralax()
	{
		Vector2 origin = { 0.0f, 0.0f };

		Rectangle sourceRec = { 0.0f, 0.0f, static_cast<float>(SPRITE::sprites.space.width), static_cast<float>(SPRITE::sprites.space.height) };

		Rectangle destRec = { 0, SPRITE::sprites_Movement.space, PROGRAM_DATA::screen_Width, PROGRAM_DATA::screen_Height };
		DrawTexturePro(SPRITE::sprites.space, sourceRec, destRec, origin, 0.0f, WHITE);

		destRec = { 0, PROGRAM_DATA::screen_Height + SPRITE::sprites_Movement.space, PROGRAM_DATA::screen_Width, PROGRAM_DATA::screen_Height };
		DrawTexturePro(SPRITE::sprites.space, sourceRec, destRec, origin, 0.0f, WHITE);
	}
}