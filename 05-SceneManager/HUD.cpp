#include "HUD.h"
#include "Animation.h"
#include "Animations.h"
#include <string>

HUD::HUD(float x, float y)
{
	this->x = x;
	this->y = y;
}

void HUD::Render(CMario* mario, int time)
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_HUD)->Render(x, y);

	int times  = ( GetTickCount64() - startTime )/1000 ;

	int stack = 0 ;
	if(mario->getLevel()  == MARIO_LEVEL_RACOON) {
		stack = ((mario->GetVx() - MARIO_ACCEL_WALK_X) / (MARIO_FLYING_CONDITION_SPEED - MARIO_ACCEL_WALK_X) ) * 7 ; // ENUM: 1,2,3,4,5,6,7 
	} 

	_char.Draw(x - ADJUST_X_WORLD, y - ADJUST_Y_WORLD, FillNumber(std::to_string(1), NUMBER_WORLD));
	_char.Draw(x + ADJUST_X_COIN, y - ADJUST_Y_COIN, FillNumber(std::to_string(mario->GetCoin()), NUMBER_COIN));
	_char.Draw(x + ADJUST_X_TIME, y + ADJUST_Y_TIME, FillNumber(std::to_string(time), NUMBER_TIME));

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
