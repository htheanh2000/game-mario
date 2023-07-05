#include "DirectionBrick.h"
#include "PlayScene.h"
#include "GameObject.h"
#include "Koopas.h"

CDirectionBrick::CDirectionBrick(CGameObject* linkedObj): CGameObject(x, y) {
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	this->x = linkedObj->GetX();
	this->y = linkedObj->GetY();
	this->linkedObj = linkedObj;
	markY = y;
}

void CDirectionBrick::Render()
{
	RenderBoundingBox();
}

void CDirectionBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - KOOPAS_BBOX_WIDTH/2;
	t = y - KOOPAS_BBOX_HEIGHT/2;
	r = l + KOOPAS_BBOX_WIDTH;
	b = t + KOOPAS_BBOX_HEIGHT;
}

void CDirectionBrick::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	// DebugOut(L"[INFO] DirectionBrick x  %f\n", this->x);
	if(dynamic_cast<Koopas *>(linkedObj) ) {
		if(y - markY > 15) {
			DebugOut(L"[INFO] DIFF Y %f\n", markY - y );
			Koopas *koopas = dynamic_cast<Koopas *>(linkedObj);
			koopas->TurnBack();
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CDirectionBrick::OnNoCollision(DWORD dt)
{
	//x += vx * dt;
	x = linkedObj->GetX() - 16  ;
	y += vy * dt;
};

void CDirectionBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<CDirectionBrick*>(e->obj)) return; 
	if (e->ny != 0 )
	{
		vy = 0;
	}
}