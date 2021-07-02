//#include"../common_includes.h"
#include<Windows.h>
#include "../memory/memory.h"


//why am i having so much darn trouble with this motherfucker

class i_panel
{
public:
	const char* get_name(unsigned int vgui_panel) {

		typedef const char* (__thiscall* o_fn)(PVOID, unsigned int);
		return memory::call_virtual<o_fn>(this, 36)(this, vgui_panel);

	}
};

