#include "DirectionBrick.h"
#include "PlayScene.h"
#include "GameObject.h"
#include "Koopas.h"

CDirectionBrick::CDirectionBrick(float x, float y): CGameObject(x, y) {
	this->ax = 0;
	this->ay = DBRICK_GRAVITY;
}

void CDirectionBrick::Render()
{
	RenderBoundingBox();
}

void CDirectionBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - DBRICK_BBOX_WIDTH/2;
	t = y - DBRICK_BBOX_HEIGHT/2;
	r = l + DBRICK_BBOX_WIDTH;
	b = t + DBRICK_BBOX_HEIGHT;
}

void CDirectionBrick::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	// vx += ax * dt;

	// DebugOut(L"[INFO] DirectionBrick x  %f\n", this->x);
	// DebugOut(L"[INFO] DirectionBrick y  %f\n", this->y);

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CDirectionBrick::OnNoCollision(DWORD dt)
{
	// x += vx * dt;
	y += vy * dt;
};

void CDirectionBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CDirectionBrick*>(e->obj)) return; 


	if (dynamic_cast<Koopas*>(e->obj) ) {
		DebugOut(L"[INFO] this->x += 15; %f\n", e->obj->GetX());
		// this->x = e->obj->GetX() + 15;
		Koopas *koopas = dynamic_cast<Koopas *>(e->obj);
		if( !isLinked) {
			isLinked = true;
		}
		else if (this->vy > 0.08) {
			this->isDeleted = true; 
			// DebugOut(L"[INFO] Should go back %f\n", this->vy);
			koopas->TurnBack() ;
		}
	}; 

	if (e->ny != 0 )
	{
		vy = 0;
	}
}