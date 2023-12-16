#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_SPRITE_SOFTBRICK 20000

#define SOFTBRICK_BBOX_WIDTH 16
#define SOFTBRICK_BBOX_HEIGHT 16

#define SOFTBRICK_STATE_DEFAULT 100
#define SOFTBRICK_STATE_BROKEN 200


#define COIN_TO_BRICK_DURATION 5000
class SoftBrick : public CGameObject {
public:
	ULONGLONG pressedStart = 0 ;
	SoftBrick(float x, float y) : CGameObject(x, y) {
		state = SOFTBRICK_STATE_DEFAULT ;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() ;
};