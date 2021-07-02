#pragma once

#include "../interfaces/interfaces.h"
#include "../interfaces/i_surface.h"

namespace render_manager {

	namespace fonts {

		extern DWORD main_font;

	}

	void init();
	void rect(int x, int y, int w, int h, color color);
	void filled_rect(int x, int y, int w, int h, color color);
	void line(int x1, int y1, int x2, int y2, color color);
	void text(const char* text, int x, int y, int font, color color);
	void vertical_gradient_rect(int x, int y, int w, int h, color top, color bottom);
	void horizontal_gradient_rect(int x, int y, int w, int h, color left, color right);
	void circle(int x, int y, int radius, color color);

}