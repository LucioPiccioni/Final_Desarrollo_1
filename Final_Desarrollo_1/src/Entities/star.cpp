#include "star.h"

#include "Program/program_Data.h"

#include "Res/sprites.h"
#include <cmath>

namespace STAR
{
	Star spawner()
	{
		const int SPAWN_AREA_TOP = static_cast<int>((PROGRAM_DATA::screen_Height - (PROGRAM_DATA::screen_Height / 3)) / 2);
		const int SPAWN_AREA_BOTTOM = static_cast<int>((PROGRAM_DATA::screen_Height + (PROGRAM_DATA::screen_Height / 3)) / 2);

		const int SPAWN_AREA_LEFT = static_cast<int>((PROGRAM_DATA::screen_Width - (PROGRAM_DATA::screen_Width / 3)) / 2);
		const int SPAWN_AREA_RIGHT = static_cast<int>((PROGRAM_DATA::screen_Width + (PROGRAM_DATA::screen_Width / 3)) / 2);

		Star new_Star;

		new_Star.rect.width = 32;
		new_Star.rect.height = 32;

		bool valid_Position = false;
		const float min_Distance = 15.0f;

		while (!valid_Position) 
		{
			new_Star.rect.x = static_cast<float>(GetRandomValue(static_cast<int>(SPAWN_AREA_LEFT) + static_cast<int>(new_Star.rect.width), SPAWN_AREA_RIGHT));
			new_Star.rect.y = static_cast<float>(GetRandomValue(SPAWN_AREA_TOP + static_cast<int>(new_Star.rect.height), SPAWN_AREA_BOTTOM));

			valid_Position = isValidPosition(new_Star, new_Star.rect, min_Distance);
		}

		new_Star.active = true;

		return new_Star;
	}

	bool isValidPosition(Star newStar, Rectangle actual_Pos, float min_Distance)
	{

		float distance_X = newStar.rect.x - (actual_Pos.x + actual_Pos.width / 2);
		float distance_Y = newStar.rect.y - (actual_Pos.y + actual_Pos.height / 2);

		float distance = sqrt(distance_X * distance_X + distance_Y * distance_Y);

		return distance >= min_Distance;
	}

	void draw(Rectangle rect)
	{
#ifdef _DEBUG
		DrawRectangleRec(rect, GREEN);
#endif

		DrawTexturePro(
			SPRITE::sprites.star,
			Rectangle{ 0, 0, static_cast<float>(SPRITE::sprites.star.width), static_cast<float>(SPRITE::sprites.star.height) },
			Rectangle{ rect.x, rect.y, rect.width, rect.height },
			Vector2{ 0, 0 },
			0.0f,
			WHITE
		);
	}
}
