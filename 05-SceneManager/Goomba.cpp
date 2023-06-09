#include "Goomba.h"
#include "Koopas.h"

CGoomba::CGoomba(float x, float y, int type):CGameObject(x, y)
{
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	deflect_start = -1;
	jump_start = GetTickCount64();
	if(type == NORMAL_GOOMBA) {
		lifeCount = 1;
	}
	else if (type == RED_GOOMBA) {
		lifeCount = 2;
	}
 	this->objType = type; // There are 2 types of objects
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{ 
		left = x - GOOMBA_BBOX_WIDTH/2;
		top = y - GOOMBA_BBOX_HEIGHT/2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CGoomba*>(e->obj)) return; 
	if (dynamic_cast<Koopas*>(e->obj)) {
		this->Hit();
	};

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (objType == RED_GOOMBA && (state== GOOMBA_STATE_WALKING) && (GetTickCount64() - jump_start > GOOMBA_JUMP_TIMEOUT) )
	{
		vy =  -GOOMBA_JUMP_SPEED ; ;
		jump_start = GetTickCount64();
		return;
	}

	if ( (state==GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT) )
	{
		isDeleted = true;
		return;
	}

	if ( (state == GOOMBA_STATE_DEFLECT) && (GetTickCount64() - deflect_start > GOOMBA_DEFLECT_TIMEOUT) )
	{
		state = GOOMBA_STATE_DIE;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = -1;
	if (objType == NORMAL_GOOMBA) {
		aniId = ID_ANI_GOOMBA_WALKING;
		if (state == GOOMBA_STATE_DIE)
		{
			aniId = ID_ANI_GOOMBA_DIE;
		}
	}
	else
	{
		if (state == GOOMBA_STATE_DIE) // dead groomba
		{
			aniId = ID_RED_GOOMBA_DIE;
		}
		else if(lifeCount == 1) { // unwind red goomba
			aniId = ID_RED_GOOMBA_WALKING;
		}
		else { // wind red goomba
			aniId = ID_RED_GOOMBA_WING_WALKING;
		}
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x,y);
	// RenderBoundingBox();
}

void CGoomba::Hit() {
	if(lifeCount == 1) {
		vy = -GOOMBA_DEFLECT_SPEED ; 
		vx = 0;
		state = GOOMBA_STATE_DEFLECT ;
		deflect_start = GetTickCount64();
	}
	else {
		lifeCount -= 1; // It should be 2 - 1 = 1 life count
	}
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			die_start = GetTickCount64();
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE)/2;
			vx = 0;
			vy = 0;
			ay = 0; 
			break;
		case GOOMBA_STATE_WALKING: 
			vx = -GOOMBA_WALKING_SPEED;
			break;
	}
}
