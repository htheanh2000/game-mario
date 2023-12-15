#include "SoftBrick.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Coin.h"
#include "Game.h"
void SoftBrick::Render()
{
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	int ani = ID_SPRITE_SOFTBRICK ;
	// DebugOut(L"[INFO] mario->pressedButton: %d\n", state);

	if(state == SOFTBRICK_STATE_BROKEN ) {
		ani = ID_ANI_COIN ;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ani)->Render(x, y);

	//RenderBoundingBox();
}

int SoftBrick::IsBlocking() {
	// CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	if(state == SOFTBRICK_STATE_BROKEN) {
		return 0  ;
	}
	return 1;
}

void SoftBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if(mario->pressedButton) {
		this->SetState(SOFTBRICK_STATE_BROKEN) ;
		pressedStart = GetTickCount64();
	}

	if(pressedStart + COIN_TO_BRICK_DURATION < GetTickCount64()) {
			this->SetState(SOFTBRICK_STATE_DEFAULT) ;
			mario->pressedButton = false;
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void SoftBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - SOFTBRICK_BBOX_WIDTH / 2;
	t = y - SOFTBRICK_BBOX_HEIGHT / 2;
	r = l + SOFTBRICK_BBOX_WIDTH;
	b = t + SOFTBRICK_BBOX_HEIGHT;

}
