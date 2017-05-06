#ifndef INPUT_H
#define INPUT_H

// std includes
#include <cstdint>
#include <vector>

namespace mirage
{
	namespace input
	{
		enum KBK_State_t : uint8_t
		{
			KBK_RELEASED = 0,
			KBK_PRESS = 1,
			KBK_REPEAT = 2
		};

		extern std::vector<KBK_State_t> KB_KEYS;
		extern std::vector<bool> MS_BUTTONS;
		extern float MS_POS_X;
		extern float MS_POS_Y;
	}
}

#endif // INPUT_H