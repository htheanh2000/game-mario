#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_SPRITE_SOFTBRICK 20000

#define SOFTBRICK_BBOX_WIDTH 16
#define SOFTBRICK_BBOX_HEIGHT 16

class SoftBrick : public CGameObject {
public:
	SoftBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() ;
};