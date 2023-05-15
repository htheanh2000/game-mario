#pragma once

#include "GameObject.h"

#define NORMAL_BLOCK 1
#define ENEMIES_ONLY_BLOCK 2

class CBGBlock :
	public CGameObject
{
public:
	float width;
	float height;

	CBGBlock(float x, float y, float width, float height, int type);
	void Render() {
		RenderBoundingBox();
	};//RenderBoundingBox(); 
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {};
	// int IsBlocking() {return 0;} ;
	int IsMarioBlocking() {return this->objType == NORMAL_BLOCK;}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};

