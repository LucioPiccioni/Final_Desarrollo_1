#include "sprites.h"

#include "program_Data.h"
#include "platform.h"

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