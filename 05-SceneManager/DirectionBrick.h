#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_DBRICK 10000
#define DBRICK_WIDTH 16
#define DBRICK_BBOX_WIDTH 4
#define DBRICK_BBOX_HEIGHT 4

#define  DBRICK_GRAVITY 0.002f
class CDirectionBrick : public CGameObject {
public:

    float ax;				
	float ay; 
	BOOLEAN isLinked = false;

	CDirectionBrick(float x, float y) ;
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
    virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
};