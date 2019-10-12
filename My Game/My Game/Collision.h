#ifndef _COLLISION_H
#define _COLLISION_H
#include "Entity.h"
#include "Game.h"
#include <vector>
#include <algorithm>

struct CCollisionEvent;
struct CCollision;
typedef CCollisionEvent* LPCOLLISIONEVENT;
typedef CCollision* LPCOLLISION;

struct CCollisionEvent
{
	Entity* entity;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, Entity* entity = NULL);
	
	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b);
};

struct CCollision {
	static LPCOLLISIONEVENT SweptAABBEx(Entity* ent1, Entity* ent2, float frameTime);

	static void SweptAABB(
		float ml, //move left
		float mt, //move top
		float mr, //move right
		float mb, //move bottom
		float dx,
		float dy,
		float sl, //static left
		float st, //static top
		float sr, //static right
		float sb, //static bottom
		float& t,
		float& nx,
		float& ny);

	static void CalcPotentialCollisions(Entity* ent,std::vector<Entity*>* coEntities, std::vector<LPCOLLISIONEVENT>& coEvents, float frameTime);
	static void FilterCollision(
		std::vector<LPCOLLISIONEVENT>& coEvents,
		std::vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny);
};

#endif // !1
