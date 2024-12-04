#pragma once

#include "raylib.h"

namespace SPRITE
{
	struct SpriteMovement
	{
		float space = 0.0f;
	};

	struct Sprites
	{
		Texture2D player_Idle;
		Texture2D player_Jump;
		Texture2D player_Run;

		Texture2D star;
		Texture2D platform;

		Texture2D space;
	};

	extern Sprites sprites;
	extern SpriteMovement spritesMovement;
	extern const int animationTotalFrames;

	void init();
	void unload();

	void update_Paralax_Pos(float delta_Time);

	void draw_Paralax();
}