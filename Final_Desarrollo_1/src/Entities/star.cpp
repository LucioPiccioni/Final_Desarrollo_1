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

		Star newStar;

		newStar.rect.width = 32;
		newStar.rect.height = 32;

		bool validPosition = false;
		const float minDistance = 15.0f;

		while (!validPosition) 
		{
			newStar.rect.x = static_cast<float>(GetRandomValue(static_cast<int>(SPAWN_AREA_LEFT) + static_cast<int>(newStar.rect.width), SPAWN_AREA_RIGHT));
			newStar.rect.y = static_cast<float>(GetRandomValue(SPAWN_AREA_TOP + static_cast<int>(newStar.rect.height), SPAWN_AREA_BOTTOM));

			validPosition = isValidPosition(newStar, newStar.rect, minDistance);
		}

		newStar.active = true;

		return newStar;
	}

	bool isValidPosition(Star newStar, Rectangle actual_Pos, float min_Distance)
	{

		float dx = newStar.rect.x - (actual_Pos.x + actual_Pos.width / 2);
		float dy = newStar.rect.y - (actual_Pos.y + actual_Pos.height / 2);

		float distance = sqrt(dx * dx + dy * dy);

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
