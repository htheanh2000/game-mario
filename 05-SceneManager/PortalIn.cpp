#include "PortalIn.h"
#include "Mario.h"
#include "PlayScene.h"

PortalIn::PortalIn(float x, float y, float w, float h, int direction, float cx, float cy, int scene)
{
	this->x = x;
	this->y = y;

	this->cx = cx;
	this->cy = cy;

	this->width = w;
	this->height = h;

	this->portal_dir = direction;

	isActive = false;
	this->sceneNo = scene;
}

void PortalIn::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void PortalIn::Render()
{
	// RenderBoundingBox();
}

void PortalIn::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - width / 2;
	top = y - height / 2;
	right = left + width;
	bottom = top + height;
}
