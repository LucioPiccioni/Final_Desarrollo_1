#include "raylib.h"

namespace STAR
{
	struct Star
	{
		Rectangle rect = {};

		bool active = false;
	};

	const int star_Point_Given = 2;

	const Vector2 min_Speed = { 10, 100 };
	extern float speed_y;
	const Vector2 max_Speed = { 200, 200 };

	const float max_length = 240;
	extern float actual_length;
	const float min_length = 100;

	Star spawner();

	bool isValidPosition(Star newStar, Rectangle actual_Pos, float min_Distance);

	void draw(Rectangle rect);
}