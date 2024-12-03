#include "raylib.h"

#include "Program/program_Data.h"
#include "Program/program_Manager.h"

namespace CONFIRM_EXIT
{
	void init();

	void update(PROGRAM_MANAGER::State_Manager& state_manager);

	void draw(Font font);
}