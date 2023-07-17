#include "HUD.h"
#include "Animation.h"
#include "Animations.h"

HUD::HUD(float x, float y)
{
	this->x = x;
	this->y = y;
}

void HUD::Render(CMario* mario, int remainingTime)
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_HUD)->Render(x, y);

	power = new PowerBar(x - ADJUST_X_POWER, y - ADJUST_Y_POWER, mario->GetVx());
	power->Render();
	//score
	//time
	//live
}

string HUD::FillNumber(string s, UINT fillNumber)
{
	while (s.size() < fillNumber) {
		s = "0" + s;
	}
	return s;
}
