#include "platform.h"

#include "raylib.h"

#include "Program/program_Data.h"
#include "Res/sprites.h"

namespace PLATFORM
{
	float speed_y = min_Speed.y;
	float actual_length = max_length;

	Platform spawner()
	{
		const float height = 20;

		Platform new_Platform;

		new_Platform.active = true;

		new_Platform.rect_Pos.width = actual_length;

		new_Platform.rect_Pos.height = height;

		new_Platform.rect_Pos.x = static_cast<float>(
			GetRandomValue(0, static_cast<int>(PROGRAM_DATA::screen_Width - new_Platform.rect_Pos.width)));

		new_Platform.speed.y = PLATFORM::speed_y;

		if (GetRandomValue(0, 1) == 1)
		{
			new_Platform.moves_In_x = true;

			new_Platform.speed.x = static_cast<float>(
				GetRandomValue(static_cast<int>(PLATFORM::min_Speed.x), static_cast<int>(PLATFORM::max_Speed.x)));

			if (GetRandomValue(0, 1) == 1)
			{
				new_Platform.right_Movement = true;
				new_Platform.left_Movement = false;
			}
			else
			{
				new_Platform.left_Movement = true;
				new_Platform.right_Movement = false;
			}
		}

		new_Platform.rect_Pos.y = -new_Platform.rect_Pos.height;

		new_Platform.rect_Dest.x = 0;
		new_Platform.rect_Dest.y = 0;
		new_Platform.rect_Dest.width = new_Platform.rect_Pos.width;
		new_Platform.rect_Dest.width = new_Platform.rect_Pos.height;

		return new_Platform;
	}

	void update(Platform& platform, float delta_Time)
	{
		move(platform, delta_Time);
		changeDirectionX(platform);
	}

	void move(Platform& platform, float delta_Time)
	{
		platform.rect_Pos.y += speed_y * delta_Time;

		if (platform.moves_In_x)
		{
			if (platform.left_Movement)
			{
				platform.rect_Pos.x -= platform.speed.x * delta_Time;
			}
			else if (platform.right_Movement)
			{
				platform.rect_Pos.x += platform.speed.x * delta_Time;
			}
		}
	}

	void changeDirectionX(Platform& platform)
	{
		if (platform.rect_Pos.x + platform.rect_Pos.width > PROGRAM_DATA::screen_Width)
		{
			platform.right_Movement = false;
			platform.left_Movement = true;
		}
		else if (platform.rect_Pos.x < 0)
		{
			platform.left_Movement = false;
			platform.right_Movement = true;
		}
	}

	void draw(Rectangle rect)
	{
#ifdef _DEBUG
		DrawRectangleRec(rect, YELLOW);
#endif

		DrawTexturePro(
			SPRITE::sprites.platform,
			Rectangle{ 0,0, rect.width, rect.height },
			rect,
			Vector2{ 0,0 },
			0,
			WHITE);
	}

}