#pragma once
#include "GameObject.h"

#define ID_ANI_GRASS 80000
#define BBOX_GRASS_WIDTH 13
#define BBOX_GRASS_HEIGHT 12


#define START_GATE 	0
#define WORLD_1 	1
#define WORLD_2 	2
#define WORLD_3 	3
#define WORLD_4 	4
#define WORLD_5 	5
#define WORLD_6 	6
class Grass :
    public CGameObject
{
public:
	int ani_id = -1;

	Grass(float x, float y) : CGameObject(x, y) {}
	Grass(float x, float y, int ani_id) : CGameObject(x, y) {
		this->ani_id = ani_id;
	};
	virtual void Render();
	int GetGate();
	int IsBlocking() { return ani_id == 80000 || ani_id == 88888; }
	void Update(DWORD dt) {};
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

