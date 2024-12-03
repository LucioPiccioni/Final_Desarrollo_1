#pragma once

namespace PROGRAM_MANAGER
{
	enum class Program_State
	{
		NONE,

		MAIN_MENU,

		GAMEPLAY,
		PAUSE,
		GAME_OVER,
		REPLAY,

		RULES,
		CREDITS,

		WANT_TO_EXIT,
		CONFIRM_EXIT,
		CANCEL_EXIT,

	};

	struct State_Manager
	{
		Program_State actual;
		Program_State previus;
	};
}