#include "FirePiranhaPlant.h"
#include "debug.h"

FirePiranhaPlant::FirePiranhaPlant(float x, float y, int type)
{
	this->objType = type;
	this->maxY = y + FIRE_PLANT_MAX_HEIGHT - 5 ;// TODO: investigate bad UI rendering if dont -5 !!;
	vy = FIRE_PLANT_SPEED;
	this->minY = y;

}

void FirePiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (objType == FPP_BIG) {
		left = x - FPP_BBOX_WIDTH / 2;
		top = y - FPP_BIG_BBOX_HEIGHT / 2;
		right = left + FPP_BBOX_WIDTH;
		bottom = top + FPP_BIG_BBOX_HEIGHT;
	}
	else {
		left = x - FPP_BBOX_WIDTH / 2;
		top = y - FPP_SMALL_BBOX_HEIGHT / 2;
		right = left + FPP_BBOX_WIDTH;
		bottom = top + FPP_SMALL_BBOX_HEIGHT;
	}
}

void FirePiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// DebugOut(L"[INFO] y %f \n" , y);
	// DebugOut(L"[INFO] maxY %f \n" , maxY);
	// DebugOut(L"[INFO] minY %f \n" , minY);
	// DebugOut(L"[INFO] vy %f \n" , vy);
	if(y >= maxY) {
		y = maxY ;
		vy = -FIRE_PLANT_SPEED ;
	}
	else if (y <= minY) {
		y = minY ;
		vy = FIRE_PLANT_SPEED ;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void FirePiranhaPlant::Render()
{
	int aniId = ID_ANI_FPP_LEFT_BOTTOM;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	// RenderBoundingBox();
}

void FirePiranhaPlant::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
