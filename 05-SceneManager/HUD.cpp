#include "HUD.h"
#include "Animation.h"
#include "Animations.h"

HUD::HUD(float x, float y)
{
	this->x = x;
	this->y = y;
}

void HUD::Render(CMario* mario, int time)
{
	// CAnimations* animations = CAnimations::GetInstance();
	// animations->Get(ID_ANI_HUD)->Render(x, y);
}

