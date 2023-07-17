#include "PButton.h"

void PButton::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI)->Render(x, y);

	RenderBoundingBox();
}

void PButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	t = y - PBUTTON_BBOX_HEIGHT / 2;
	l = x - PBUTTON_BBOX_WIDTH / 2;
	r = l + PBUTTON_BBOX_WIDTH;
	b = t + PBUTTON_BBOX_HEIGHT;
}