#include "Koopas.h"

#include "Utils.h"

Koopas::Koopas(float x, float y, int model) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	this->objType = model;
	this->vx = -KOOPAS_SPEED;
}

void Koopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	int bwidth = KOOPAS_BBOX_WIDTH ;
	int bheight = KOOPAS_BBOX_HEIGHT ;

	if(state == KOOPAS_STATE_DEFEND) {
		bheight = KOOPAS_DEFEND_BBOX_HEIGHT ; //Update the bounding box after chagne animation
	}

	left = x - bwidth / 2;
	top = y - bheight / 2;
	right = left + bwidth;
	bottom = top + bheight;
}

void Koopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if(state == KOOPAS_STATE_DEFEND) {
		vx = 0;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void Koopas::Render()
{
	int aniId = ID_ANI_KOOPAS_WALKING_RIGHT;

	if (objType == KOOPAS_GREEN_WING) {
		if (vx > 0) {
			aniId = ID_ANI_KOOPAS_GREEN_WING_RIGHT;
		}
		else {
			aniId = ID_ANI_KOOPAS_GREEN_WING_LEFT;
		}
	}

	if (objType == KOOPAS_GREEN) {
		if (vx > 0) {
			aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
		}
		else {
			aniId = ID_ANI_KOOPAS_WALKING_LEFT;
		}
	}

	if (state == KOOPAS_STATE_DEFEND) {
		aniId = ID_ANI_KOOPAS_DEFEND ;
	}


	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	// RenderBoundingBox();
}


int Koopas::IsCollidable()
{
    return 1;
}

void Koopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void Koopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<Koopas*>(e->obj)) return; 

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

