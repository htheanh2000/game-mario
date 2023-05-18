#include "SoftBrick.h"

void SoftBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_SPRITE_SOFTBRICK)->Render(x, y);

	//RenderBoundingBox();
}

void SoftBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SOFTBRICK_BBOX_WIDTH / 2;
	t = y - SOFTBRICK_BBOX_HEIGHT / 2;
	r = l + SOFTBRICK_BBOX_WIDTH;
	b = t + SOFTBRICK_BBOX_HEIGHT;

}
