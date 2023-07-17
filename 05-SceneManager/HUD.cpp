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


	int stack = 0 ;
	if(mario->getLevel()  == MARIO_LEVEL_RACOON) {
		((mario->GetVx() - MARIO_ACCEL_WALK_X) / (MARIO_FLYING_CONDITION_SPEED - MARIO_ACCEL_WALK_X) ) * 7 ; // ENUM: 1,2,3,4,5,6,7 
	} 
	power = new PowerBar(x - ADJUST_X_POWER, y - ADJUST_Y_POWER, stack);
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
