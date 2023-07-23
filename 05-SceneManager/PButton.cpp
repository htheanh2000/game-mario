#include "PButton.h"
#include "Mario.h"

void PButton::Render()
{
	int ani = -1 ;
	CAnimations* animations = CAnimations::GetInstance();
	if(state == STATE_UNBREAKED) {
		ani = ID_ANI_SOFTBRICK ;
	}
	else if(state == STATE_BREAK)  {
		ani = ID_ANI;
	}
	else  {
		ani = ID_ANI_PRESSED;
	}

	if(jumpedOn) {
		ani = ID_ANI_PRESSED;
	}
	animations->Get(ani)->Render(x, y);
	// RenderBoundingBox();
}

void PButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
	if(!jumpedOn) {
		t = y - PBUTTON_BBOX_HEIGHT / 2;
		l = x - PBUTTON_BBOX_WIDTH / 2;
		r = l + PBUTTON_BBOX_WIDTH;
		b = t + PBUTTON_BBOX_HEIGHT;
	}
	else {
		t = y - PBUTTON_BBOX_JUMPED_HEIGHT / 2 + 5;
		l = x - PBUTTON_BBOX_WIDTH / 2;
		r = l + PBUTTON_BBOX_WIDTH;
		b = t + PBUTTON_BBOX_JUMPED_HEIGHT / 2;
	}
	
}

void PButton::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
}
void PButton::OnNoCollision(DWORD dt)
{
	if(!jumpedOn) {
		state = STATE_UNBREAKED ;
	}
};
