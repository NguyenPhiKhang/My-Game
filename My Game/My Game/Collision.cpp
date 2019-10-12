#include "Collision.h"

CCollisionEvent::CCollisionEvent(float t, float nx, float ny, Entity* entity)
{
	this->t = t; this->nx = nx; this->ny = ny; this->entity = entity;
}

bool CCollisionEvent::compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
{
	return a->t < b->t;
}

LPCOLLISIONEVENT CCollision::SweptAABBEx(Entity* ent1, Entity* ent2, float frameTime)
{
	float sl, st, sr, sb;		//static object bbox (Rect của object)
	float ml, mt, mr, mb;		//move object bbox (Rect của main)
	float t, nx, ny;

	ent2->getBoundingBox(sl, st, sr, sb); //get tọa độ của object

	//deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	svx = ent2->getVelocity().x;
	svy = ent2->getVelocity().y;

	float sdx = svx * frameTime; //khoảng cách x object đi được sau khoảng dt
	float sdy = svy * frameTime; //khoảng cách y object đi được sau khoảng dt

	float dx = ent1->getDX() - sdx; //khoảng cách dx giữa main và object
	float dy = ent1->getDY() - sdy; //khoảng cách dy giữa main và object

	ent1->getBoundingBox(ml, mt, mr, mb);

	//Xét va chạm
	SweptAABB(
		ml, mt, mr, mb, //tọa độ main
		dx, dy, //khoảng cách giữa main vs object
		sl, st, sr, sb, //tọa độ object
		t, nx, ny); //điều kiện xét có va chạm hay không?

	CCollisionEvent* e = new CCollisionEvent(t, nx, ny, ent2);
	return e;
}

void CCollision::SweptAABB(
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
	float& ny)
{
	float xInvEntry, yInvEntry, xEntry, yEntry;
	float xInvExit, yInvExit, xExit, yExit;

	float EntryTime;
	float ExitTime;

	t = -1.0f;		//no collision
	nx = ny = 0;

	//
	// Board-phase test: kiểm tra main và object CÓ THỂ va chạm hay không?
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br <sl || bl>sr || bb<st || bt>sb) return;

	if (dx == 0 && dy == 0) return; // moving object is not moving > obvious no collision

	if (dx > 0)
	{
		xInvEntry = sl - mr;
		xInvExit = sr - ml;
	}
	else if (dx < 0)
	{
		xInvEntry = sr - ml;
		xInvExit = sl - mr;
	}

	if (dy > 0)
	{
		yInvEntry = st - mb;
		yInvExit = sb - mt;
	}
	else if (dy < 0)
	{
		yInvEntry = sb - mt;
		yInvExit = st - mb;
	}

	if (dx == 0)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / dx;
		xExit = xInvExit / dx;
	}

	if (dy == 0)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / dy;
		yExit = yInvExit / dy;
	}

	if ((xEntry < 0.0f && yEntry < 0.0f) || xEntry > 1.0f || yEntry > 1.0f) return;

	EntryTime = max(xEntry, yEntry); //thời gian bắt đầu va chạm lớn nhất ( vì nếu thời gian lớn nhất sẽ thỏa điều kiện va chạm)
	ExitTime = min(xExit, yExit); //thời gian ngắn nhất khi 2 vật thể hết va chạm nhau

	if (EntryTime > ExitTime) return;

	t = EntryTime;

	if (xEntry > yEntry)
	{
		ny = 0.0f;
		nx = dx > 0 ? -1.0f : 1.0f;
	}
	else
	{
		nx = 0.0f;
		ny = dy > 0 ? -1.0f : 1.0f;
	}
}

void CCollision::CalcPotentialCollisions(Entity* ent ,std::vector<Entity*>* coEntities, std::vector<LPCOLLISIONEVENT>& coEvents, float frameTime)
{
	for (UINT i = 0; i < coEntities->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(ent, coEntities->at(i), frameTime);

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);

}

void CCollision::FilterCollision(std::vector<LPCOLLISIONEVENT>& coEvents, std::vector<LPCOLLISIONEVENT>& coEventsResult, float& min_tx, float& min_ty, float& nx, float& ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0)
		{
			min_tx = c->t; nx = c->nx; min_ix = i;
		}
		if (c->t < min_ty && c->ny != 0)
		{
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}
	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}
