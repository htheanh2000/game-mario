#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI 12000
#define ID_ANI_PRESSED 12001

#define PBUTTON_BBOX_WIDTH 16
#define PBUTTON_BBOX_HEIGHT 16

class PButton : public CGameObject {
public:
	PButton(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};