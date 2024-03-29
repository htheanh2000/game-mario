#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI 12000
#define ID_ANI_PRESSED 12001
#define ID_ANI_SOFTBRICK 20000

#define PBUTTON_BBOX_WIDTH 16
#define PBUTTON_BBOX_HEIGHT 16
#define PBUTTON_BBOX_JUMPED_HEIGHT 8

#define STATE_UNBREAKED	1
#define STATE_BREAK	2
#define STATE_JUMPED_ON	3

#define BUTTON_TO_BRICK_DURATION 5000
class PButton : public CGameObject {
public:
	ULONGLONG pressedStart = 0 ;
	int state = STATE_UNBREAKED;
	int jumpedOn = 0;
	PButton(float x, float y) : CGameObject(x, y) {}
	void Render();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 1; }
	int IsCollidable() { return 1; }
	void SetState(int sta) { this->state = sta; }
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) ;
	virtual void OnNoCollision(DWORD dt) ;
};