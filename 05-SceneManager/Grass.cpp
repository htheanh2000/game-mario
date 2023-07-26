#include "Grass.h"

void Grass::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if(ani_id != 88888) {
		animations->Get(this->ani_id)->Render(x, y);
	}
	// if(ani_id == 80007) {
	// 	RenderBoundingBox();
	// }
}

int Grass::GetGate() 
{
	// if(ani_id == 80000) {
	// 	return 1;
	// }
	if(ani_id == 80001) {
		return 1;
	}
	else if(ani_id == 80002) {
		return 2;
	}
	else if(ani_id == 80003) {
		return 3;
	}
	else if(ani_id == 80004) {
		return 4;
	}
	else if(ani_id == 80005) {
		return 5;
	}
	else if(ani_id == 80006) {
		return 6;
	}
	else if(ani_id == 80007) {
		return 0;
	}
	else return -1 ;
}

void Grass::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	
	l = x - BBOX_GRASS_WIDTH/2;
	t = y - BBOX_GRASS_HEIGHT/2;
	r = l + BBOX_GRASS_WIDTH;
	b = t + BBOX_GRASS_HEIGHT;
}
