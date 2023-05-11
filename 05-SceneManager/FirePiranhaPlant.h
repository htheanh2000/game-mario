#pragma once
#include "GameObject.h"

#define FPP_BBOX_WIDTH 16
#define FPP_BIG_BBOX_HEIGHT 33
#define FPP_SMALL_BBOX_HEIGHT 25

// BIG PIRANHA
#define ID_ANI_FPP_LEFT_TOP 500002
#define ID_ANI_FPP_LEFT_BOTTOM 500003
#define ID_ANI_FPP_LEFT_TOP_SHOOT 500004
#define ID_ANI_FPP_LEFT_BOTTOM_SHOOT 500005
#define ID_ANI_FPP_RIGHT_TOP 500006
#define ID_ANI_FPP_RIGHT_BOTTOM 500007
#define ID_ANI_FPP_RIGHT_TOP_SHOOT 500008
#define ID_ANI_FPP_RIGHT_BOTTOM_SHOOT 500009

// SMALL PIRANHA
#define ID_ANI_FPP_SMALL_LEFT_TOP 500010
#define ID_ANI_FPP_SMALL_LEFT_BOTTOM 500011
#define ID_ANI_FPP_SMALL_LEFT_TOP_SHOOT 500012
#define ID_ANI_FPP_SMALL_LEFT_BOTTOM_SHOOT 500013
#define ID_ANI_FPP_SMALL_RIGHT_TOP 500014
#define ID_ANI_FPP_SMALL_RIGHT_BOTTOM 500015
#define ID_ANI_FPP_SMALL_RIGHT_TOP_SHOOT 500016
#define ID_ANI_FPP_SMALL_RIGHT_BOTTOM_SHOOT 500017

// MODEL
#define FPP_BIG 1
#define FPP_SMALL 2

#define FIRE_PLANT_SPEED 0.02f
#define FIRE_PLANT_MAX_HEIGHT 50

class FirePiranhaPlant :
    public CGameObject
{
protected:
	float ax;
	float ay;
	float maxY  ;
	float minY ;
    int objType;

	void Attack() ;
public:
	FirePiranhaPlant(float x, float y, int type);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
	// virtual int IsCollidable() { return 1; };
};

