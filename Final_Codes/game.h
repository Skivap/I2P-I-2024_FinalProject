#ifndef game_h
#define game_h

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "utility.h"

/*
	The state of the keys
	If the key is pressed then keyState[...] will be true
*/
extern bool keyState[ALLEGRO_KEY_MAX];
extern ALLEGRO_MOUSE_STATE mouseState;

// Function to change from one scene to another.
void change_scene(Scene next_scene);

// Initialize Game
void initGame(void);

// Start Game
void startGame(void);

#endif
