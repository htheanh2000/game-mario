#include "Star.h"

void Star::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_SPRITE_STAR)->Render(x, y);

	//RenderBoundingBox();
}

void Star::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - STAR_BBOX_WIDTH / 2;
	t = y - STAR_BBOX_HEIGHT / 2;
	r = l + STAR_BBOX_WIDTH;
	b = t + STAR_BBOX_HEIGHT;

}
