#ifndef enemy_h
#define enemy_h

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "enemy.h"
#include "utility.h"
#include "map.h"
#include "player.h"

typedef enum{
    slime,
} enemyType;

typedef enum{
    ALIVE, DYING, DEAD
} EnemyStatus;

typedef struct _enemy{
    ALLEGRO_BITMAP* image;
    
    enemyType type;
    Point coord;
    int speed;
    int health;
    
    EnemyStatus status;
    
    // Knockback
    float knockback_angle;
    uint8_t knockback_CD;
    
    // Animation
    DIRECTION dir;
    uint8_t animation_tick;
    uint8_t animation_hit_tick;
    uint8_t death_animation_tick;

} Enemy;

// Create an enemy in specified row col and the type
Enemy createEnemy(int row, int col, char type);

// Return true if the enemy is death by hit
void hitEnemy(Enemy * enemy, int damage, float angle);


/* 
    Struct of 1 node of enemy
    We use linked list data structure to store enemy information
    Since the enemy might die at one point, linked list will be better here since the deletion is O(1)
*/
typedef struct _enemyNode {
    Enemy enemy;
    struct _enemyNode * next;
} enemyNode;

enemyNode * createEnemyList(void);
void insertEnemyList(enemyNode * dummyhead, Enemy _enemy);
void updateEnemyList(enemyNode * dummyhead, Map * map, Player * player);
void drawEnemyList(enemyNode * dummyhead, Point cam);
void destroyEnemyList(enemyNode * dummyhead);

void initEnemy(void);
void terminateEnemy(void);

#endif
