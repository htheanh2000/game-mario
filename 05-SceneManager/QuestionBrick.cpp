#include "QuestionBrick.h"
#include "Brick.h"
#include "Mario.h"
#include "PlayScene.h"
#include "QBCoin.h"

void CQuestionBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - QUESTION_BRICK_BBOX_WIDTH / 2;
	top = y - QUESTION_BRICK_BBOX_HEIGHT / 2;
	right = left + QUESTION_BRICK_BBOX_WIDTH;
	bottom = top + QUESTION_BRICK_BBOX_HEIGHT;
}

void CQuestionBrick::Render()
{
	int aniId = ID_ANI_QUESTION_BRICK;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}


void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();

	if (isOpened) {
		QBCoin* coin = new QBCoin(x, y);
		coin->SetState(QB_COIN_STATE_UP);
		scene->objects.push_back(coin);
		isOpened = false;

	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}