#pragma once
#include "GameObject.h"


// Define Bbox
#define MUSHROOM_BBOX_WIDTH 	16
#define MUSHROOM_BBOX_HEIGHT 	16

// Define object type
#define RED_MUSHROOM  	1
#define GREEN_MUSHROOM  2

// Define ID animation
#define ID_RED_ANI_MUSHROOM 	105 // Red mushroom
#define ID_GREEN_ANI_MUSHROOM 	106 // Green mushroom

// define speed, gravity, ...
#define MUSHROOM_RUN_SPEED 	0.08f
#define MUSHROOM_GRAVITY 	0.003f


// define state
#define MUSHROOM_STATE_UP 	100
#define MUSHROOM_STATE_RUN 	200
#define MUSHROOM_SPEED_UP 	0.03f

class CMushroom :
    public CGameObject
{
protected:
	float ax;
	float ay;

	float minY;

public:
	CMushroom(float x, float y, int type);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual void SetState(int state);

	virtual int IsCollidable() { return 1; }
	virtual int IsBlocking() { return 0; }  
	virtual void OnNoCollision(DWORD dt); // Allow runcable objects
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};

