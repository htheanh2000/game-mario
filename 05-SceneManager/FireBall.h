#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "PlayScene.h"

#define FIREBALL_ANI    2203
#define FIRE_BALL_BBOX_WIDTH 9
#define FIRE_BALL_BBOX_HEIGHT 7


#define FIRE_BALL_GRAVITY 0.002f
#define FIRE_BALL_SPEED 0.2f

class FireBall :
	public CGameObject
{
protected:
	float ax = 0, ay = 0, tx = 0, ty = 0;
	
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
public:
	FireBall(float x, float y);
	FireBall(float x, float y, float tx, float ty);
	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
};

