#include "Grass.h"

void Grass::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(ani_id != 88888) {
		animations->Get(this->ani_id)->Render(x, y);
	}
	else {
		//RenderBoundingBox();
	}
}

void Grass::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BBOX_GRASS_WIDTH/2;
	t = y - BBOX_GRASS_HEIGHT/2;
	r = l + BBOX_GRASS_WIDTH;
	b = t + BBOX_GRASS_HEIGHT;
}
