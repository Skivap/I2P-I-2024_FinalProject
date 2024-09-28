#ifndef bullet_h
#define bullet_h

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "enemy.h"
#include "utility.h"

// Bullet
typedef struct _Bullet{
    PointFloat coord;
    float speed;
    float angle;
    float damage;
    ALLEGRO_BITMAP* image;
} Bullet;

// Linked List of Bullet
typedef struct _bulletNode{
    Bullet bullet;
    struct _bulletNode * next;
} BulletNode;

Bullet create_bullet(char* bullet_path, PointFloat coord, float angle, float speed, float damage);

BulletNode * createBulletList(void);
void insertBulletList(BulletNode * dummyhead, Bullet bullet);
void updateBulletList(BulletNode * dummyhead, enemyNode * enemyList, Map * map);
void drawBulletList(BulletNode * dummyhead, Point camera);
void destroyBulletList(BulletNode * dummyhead);

#endif /* bullet_h */
