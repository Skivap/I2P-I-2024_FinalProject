#ifndef weapon_h
#define weapon_h

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "utility.h"
#include "bullet.h"

typedef struct _Weapon{
    float angle;

    ALLEGRO_BITMAP* image;
    ALLEGRO_SAMPLE* shooting_audio;

    char* bullet_path;
    int cooldown;
    int cooldown_counter;
    int speed;
    int damage;
} Weapon;

Weapon create_weapon(char* weapon_path, char* bullet_path, int cooldown, int speed, int damage);
void update_weapon(Weapon * weapon, BulletNode * bulletList, Point playerCoord, Point cam);
void draw_weapon(Weapon * weapon, Point playerCoord, Point cam);
void delete_weapon(Weapon * weapon);

#endif /* weapon_h */
