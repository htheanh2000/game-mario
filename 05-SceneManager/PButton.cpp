#include "PButton.h"
#include "Mario.h"

void PButton::Render()
{
	int ani = -1 ;
	CAnimations* animations = CAnimations::GetInstance();
	if(state == STATE_UNBREAKED) {
		ani = ID_ANI_SOFTBRICK ;
		DebugOut(L"[INFO] STATE_UNBREAKED %f\n", 1 );
	}
	else if(state == STATE_BREAK)  {
		ani = ID_ANI;
		DebugOut(L"[INFO] STATE_BREAK %f\n", 1 );
	}
	else  {
		ani = ID_ANI_PRESSED;
		DebugOut(L"[INFO] ID_ANI_PRESSED %f\n", 1 );
	}

	if(jumpedOn) {
		ani = ID_ANI_PRESSED;
	}
	animations->Get(ani)->Render(x, y);
	RenderBoundingBox();
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
		t = y - PBUTTON_BBOX_JUMPED_HEIGHT / 2;
		l = x - PBUTTON_BBOX_WIDTH / 2;
		r = l + PBUTTON_BBOX_WIDTH;
		b = t + PBUTTON_BBOX_JUMPED_HEIGHT;
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
