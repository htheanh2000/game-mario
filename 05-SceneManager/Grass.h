#pragma once
#include "GameObject.h"

#define ID_ANI_GRASS 80000
#define BBOX_GRASS_WIDTH 16
#define BBOX_GRASS_HEIGHT 16
class Grass :
    public CGameObject
{
public:
	int ani_id = -1;

	Grass(float x, float y) : CGameObject(x, y) {}
	Grass(float x, float y, float ani_id) : CGameObject(x, y) {
		this->ani_id = ani_id;
	};
	virtual void Render();
	void Update(DWORD dt) {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

