#include "Mushroom.h"
#include "Mario.h"
#include "PlayScene.h"

CMushroom::CMushroom(float x, float y, int type) : CGameObject(x, y)
{
	this->ay = 0;
	this->ax = 0;
	this->x = x;
	this->y = y;
	objType = type;

	minY = y - MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MUSHROOM_BBOX_WIDTH / 2;
	top = y - MUSHROOM_BBOX_HEIGHT / 2;
	right = left + MUSHROOM_BBOX_WIDTH;
	bottom = top + MUSHROOM_BBOX_HEIGHT;
}

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (y <= minY)
	{
		SetState(MUSHROOM_STATE_RUN);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::Render()
{
	int aniId = ID_RED_ANI_MUSHROOM;

	if(objType == GREEN_MUSHROOM) {
		aniId = ID_GREEN_ANI_MUSHROOM;
	}
	
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_UP:
		vy = -MUSHROOM_SPEED_UP;
		break;
	case MUSHROOM_STATE_RUN:
		vx = MUSHROOM_RUN_SPEED;
		ay = MUSHROOM_GRAVITY;
		break;
	}
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
