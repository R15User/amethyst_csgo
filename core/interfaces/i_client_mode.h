
#pragma once

#include "i_client_entity.h"

class i_client_mode {

public:
	bool should_draw_entity(i_client_entity* p_entity) {

		typedef bool(__thiscall* o_fn)(void*, i_client_entity*);
		return memory::call_virtual<o_fn>(this, 14)(this, p_entity);

	}
};


/*
#pragma once
#include "i_client_entity.h"
class IPanel
{
public:
	const char* GetName(unsigned int vguiPanel)
	{
		typedef const char* (__thiscall* Fn)(IPanel*, unsigned int);
		return utilities::call_virtual<Fn>(this, 36)(this, vguiPanel);
	}
};

extern IPanel* g_pPanel;

enum class ClearFlags_t
{
	VIEW_CLEAR_COLOR = 0x1,
	VIEW_CLEAR_DEPTH = 0x2,
	VIEW_CLEAR_FULL_TARGET = 0x4,
	VIEW_NO_DRAW = 0x8,
	VIEW_CLEAR_OBEY_STENCIL = 0x10,
	VIEW_CLEAR_STENCIL = 0x20,
};

enum class MotionBlurMode_t
{
	MOTION_BLUR_DISABLE = 1,
	MOTION_BLUR_GAME = 2,
	MOTION_BLUR_SFM = 3
};


class CViewSetup
{
public:
	__int32   x;                  //0x0000 
	__int32   x_old;              //0x0004 
	__int32   y;                  //0x0008 
	__int32   y_old;              //0x000C 
	__int32   width;              //0x0010 
	__int32   width_old;          //0x0014 
	__int32   height;             //0x0018 
	__int32   height_old;         //0x001C 
	char      pad_0x0020[0x90];   //0x0020
	float     fov;                //0x00B0 
	float     viewmodel_fov;      //0x00B4 
	vec3_t    origin;             //0x00B8 
	vec3_t    angles;             //0x00C4 
	char      pad_0x00D0[0x7C];   //0x00D0

};////Size=0x014C

class IClientMode
{
public:

};
extern IClientMode* g_pClientMode;
*/