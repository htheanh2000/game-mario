#include "QuestionBrick.h"
#include "Brick.h"
#include "Mario.h"
#include "PlayScene.h"
#include "QBCoin.h"
#include "MushRoom.h"
#include "Leaf.h"

CQuestionBrick::CQuestionBrick(float x, float y, int type)
{
	this->objType = type;
}

void CQuestionBrick::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x - QUESTION_BRICK_BBOX_WIDTH / 2;
	top = y - QUESTION_BRICK_BBOX_HEIGHT / 2;
	right = left + QUESTION_BRICK_BBOX_WIDTH;
	bottom = top + QUESTION_BRICK_BBOX_HEIGHT;
}

void CQuestionBrick::Render()
{
	int aniId = ID_ANI_QUESTION_BRICK;

	if (isEmpty)
	{
		aniId = ID_ANI_QUESTION_BRICK_EMPTY;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CQuestionBrick::activateEffect()
{
	CMario *mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	CPlayScene *scene = (CPlayScene *)CGame::GetInstance()->GetCurrentScene();

	if (!isEmpty)
	{
		// TO DO: CLEAN CODE HERE

		if (objType == RED_MUSHROOM_OR_LEAF_EFFECT)
		{
			DebugOut(L"[INFO] Mario current level  %f \n", mario->GetLevel());
			if (mario->GetLevel() == MARIO_LEVEL_SMALL)
			{
				CMushroom *mushroom = new CMushroom(x, y, RED_MUSHROOM);
				mushroom->SetState(MUSHROOM_STATE_UP);
				scene->objects.push_back(mushroom);
			}

			// active leaf if mario in big state => go to mario racoon
			if (mario->GetLevel() == MARIO_LEVEL_BIG)
			{
				CLeaf *leaf = new CLeaf(x, y);
				scene->objects.push_back(leaf);
			}
		}
		else if (objType == GREEN_MUSHROOM_EFFECT) {
			CMushroom *mushroom = new CMushroom(x, y, GREEN_MUSHROOM);
			mushroom->SetState(MUSHROOM_STATE_UP);
			scene->objects.push_back(mushroom);
		}
		else // it should be 1 -> Coin
		{
			QBCoin *coin = new QBCoin(x, y);
			coin->SetState(QB_COIN_STATE_UP);
			scene->objects.push_back(coin);
			//mario->addCoin(); // add 1 coin
		}
		isEmpty = true; // Ensure only effect for each brick
						// TODO: Make brick jump after active effect
	}
}
