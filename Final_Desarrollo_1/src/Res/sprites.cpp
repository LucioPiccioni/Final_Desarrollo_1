#include "sprites.h"

#include "Program/program_Data.h"
#include "Entities/platform.h"

namespace SPRITE
{
	const int animationTotalFrames = 11;

	Sprites sprites = {};
	SpriteMovement spritesMovement = {};

	void init()
	{
		sprites.player_Idle = LoadTexture("res/Idle (32x32).png");
		sprites.player_Run = LoadTexture("res/Run (32x32).png");
		sprites.player_Jump = LoadTexture("res/Jump (32x32).png");

		sprites.platform = LoadTexture("res/platform.png");

		sprites.space = LoadTexture("res/Paralax/space.png");
	}

	void unload()
	{
		UnloadTexture(sprites.player_Idle);
		UnloadTexture(sprites.player_Run);
		UnloadTexture(sprites.player_Jump);

		UnloadTexture(sprites.platform);

		UnloadTexture(sprites.space);
	}

	void update_Paralax_Pos(float delta_Time)
	{
		float skySpeed = (PLATFORM::speed_y * 0.5f) * delta_Time;

		delta_Time = delta_Time + 2;

		if (skySpeed > 0)
			SPRITE::spritesMovement.space -= skySpeed;

		if (SPRITE::spritesMovement.space < -PROGRAM_DATA::screenHeight)
			SPRITE::spritesMovement.space = 0;
	}

	void draw_Paralax()
	{
		Vector2 origin = { 0.0f, 0.0f };

		Rectangle sourceRec = { 0.0f, 0.0f, static_cast<float>(SPRITE::sprites.space.width), static_cast<float>(SPRITE::sprites.space.height) };

		Rectangle destRec = { 0, SPRITE::spritesMovement.space, PROGRAM_DATA::screenWidth, PROGRAM_DATA::screenHeight };
		DrawTexturePro(SPRITE::sprites.space, sourceRec, destRec, origin, 0.0f, WHITE);

		destRec = { 0, PROGRAM_DATA::screenHeight + SPRITE::spritesMovement.space, PROGRAM_DATA::screenWidth, PROGRAM_DATA::screenHeight };
		DrawTexturePro(SPRITE::sprites.space, sourceRec, destRec, origin, 0.0f, WHITE);
	}
}