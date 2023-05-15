#include "BGBlock.h"

CBGBlock::CBGBlock(float x, float y, float width, float height, int type) :CGameObject(x, y)
{
	this->width = width;
	this->height = height;
	this->objType = type;
}

void CBGBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width / 2;
	r = l + width;
	t = y - height / 2;
	b = t + height;
}
