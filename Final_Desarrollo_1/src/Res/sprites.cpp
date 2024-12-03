#include "sprites.h"

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

}