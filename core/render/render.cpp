#include "render.h"

namespace render_manager {

	namespace fonts {

		DWORD main_font;

	}

}

void render_manager::init() {
	fonts::main_font = interfaces::surface->create_font();
	interfaces::surface->set_font_glyph_set(fonts::main_font, "Tahoma", 15, 500, 0, 0, FONTFLAG_OUTLINE);
}

void render_manager::rect(int x, int y, int w, int h, color color) {

	interfaces::surface->draw_set_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_outline(x, y, x + w, y + h);

}

void render_manager::filled_rect(int x, int y, int w, int h, color color) {

	interfaces::surface->draw_set_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_filled_rect(x, y, x + w, y + h);

}

void render_manager::line(int x1, int y1, int x2, int y2, color color) {

	interfaces::surface->draw_set_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_line(x1, y1, x2, y2);
}


void render_manager::text(const char* text, int x, int y, int font, color color) {

	std::string text_normal = text;
	std::wstring text_wide = std::wstring(text_normal.begin(), text_normal.end());


	interfaces::surface->draw_set_text_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_set_text_font(font);

	interfaces::surface->draw_set_text_pos(x, y);


	interfaces::surface->draw_print_text(text_wide.c_str(), text_wide.length(), FONT_DRAW_DEFAULT);

}

void render_manager::vertical_gradient_rect(int x, int y, int w, int h, color top, color bottom) {
	interfaces::surface->draw_set_color(top.r, top.g, top.b, top.a);
	interfaces::surface->draw_filled_rect_fade(x, y, w, h, 255, 255, false);
	interfaces::surface->draw_set_color(bottom.r, bottom.g, bottom.b, bottom.a);
	interfaces::surface->draw_filled_rect_fade(x, y, w, h, 0, 255, false);
}

void render_manager::horizontal_gradient_rect(int x, int y, int w, int h, color left, color right) {
	interfaces::surface->draw_set_color(left.r, left.g, left.b, left.a);
	interfaces::surface->draw_filled_rect_fade(x, y, w, h, 255, 255, true);
	interfaces::surface->draw_set_color(right.r, right.g, right.b, right.a);
	interfaces::surface->draw_filled_rect_fade(x, y, w, h, 0, 255, true);
}

void render_manager::circle(int x, int y, int radius, color color)
{
	interfaces::surface->draw_set_color(color.r, color.g, color.b, color.a);
	interfaces::surface->draw_outlined_circle(x, y, radius, 12);
}
