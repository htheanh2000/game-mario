#pragma once
#include "GameObject.h"

#define GOOMBA_GRAVITY 0.002f
#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_DEFLECT_SPEED 0.3f
#define GOOMBA_JUMP_SPEED 0.4f


#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 14
#define GOOMBA_BBOX_HEIGHT_DIE 7

#define GOOMBA_DIE_TIMEOUT 500
#define GOOMBA_DEFLECT_TIMEOUT 500
#define GOOMBA_JUMP_TIMEOUT 1500

#define GOOMBA_STATE_WALKING 100
#define GOOMBA_STATE_DIE 200
#define GOOMBA_STATE_DEFLECT 300

#define ID_ANI_GOOMBA_WALKING 5000
#define ID_ANI_GOOMBA_DIE 5001

#define ID_RED_GOOMBA_WING_WALKING 5005
#define ID_RED_GOOMBA_WALKING 5003
#define ID_RED_GOOMBA_DIE 5004

#define NORMAL_GOOMBA 1
#define RED_GOOMBA	2

#define NORMAL_GOOMBA_LIFE_COUNT 1
#define RED_GOOMBA_LIFE_COUNT	2

class CGoomba : public CGameObject
{
protected:
	float ax;				
	float ay; 
	int objType;
	int lifeCount;

	ULONGLONG die_start;
	ULONGLONG deflect_start;
	ULONGLONG jump_start;

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

	virtual int IsCollidable() { return state == GOOMBA_STATE_WALKING; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public: 	
	CGoomba(float x, float y, int type);
	virtual void SetState(int state);
	virtual void Hit();
};