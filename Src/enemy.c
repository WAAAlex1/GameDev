#include "bullet.h"
#include "util.h"
#include "entity.h"
#include "bulletManager.h"
#include "entityHandler.h"
#include "PuTTYSprites.h"
#include "vec.h"
#include "enemy.h"

void initEnemy(entity_t * entity, enemy_t * enemy, uint8_t type)
{
	enemy->entity = entity;
	enemy->type = type; // = 0 for spaceship, = 1 for 1x1 asteroid, = 2 for 2x2 asteroid and = 3 for 3x3 asteroid
}

void enemyShoot(bulletManager_t *bulletManager,entityHandler_t *entHan,enemy_t * enemy,int32_t bulletSpeed)
{
	if(getRandomInterval(0,100) >= 98) //2% chance at shooting each tick
	{
		spawnBullet(bulletManager, entHan, getXint(&(enemy->entity->pos))+1, getYint(&(enemy->entity->pos))+4,0,bulletSpeed,1,0,enemy->entity->height, 0);
	}
}

