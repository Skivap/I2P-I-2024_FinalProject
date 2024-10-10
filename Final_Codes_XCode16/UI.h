#ifndef UI_H
#define UI_H
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string.h>
#include "utility.h"

typedef struct _Button {
	int x, y, w, h;

	ALLEGRO_BITMAP* default_img;
	ALLEGRO_BITMAP* hovered_img;

	bool hovered;
}Button;

Button button_create(int x, int y, int w, int h, const char* default_image_path, const char* hovered_image_path);
void draw_button(Button button);
void update_button(Button* button);
void destroy_button(Button* button);

#endif