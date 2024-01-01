#include "GoldBrick.h"
#include "Utils.h"
#include "Mario.h"
#include "PlayScene.h"
#include "Mushroom.h"
#include "BreakBrick.h"

GoldBrick::GoldBrick(float x, float y, int model)
{
	this->objType = model;

	this->ay = 0;
	this->ax = 0;

	this->minY = y - GOLD_BRICK_BBOX_HEIGHT;
	this->startY = y;
	this->startX = x;

	SetType(EType::GOLDBRICK);
}

void GoldBrick::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x - GOLD_BRICK_BBOX_WIDTH / 2;
	top = y - GOLD_BRICK_BBOX_HEIGHT / 2;
	right = left + GOLD_BRICK_BBOX_WIDTH;
	bottom = top + GOLD_BRICK_BBOX_HEIGHT;
	if(isPress) {
		top = y  + GOLD_BRICK_PRESSED_BBOX_HEIGHT/2;
		bottom = top + GOLD_BRICK_PRESSED_BBOX_HEIGHT/2 + GOLD_BRICK_PRESSED_BBOX_HEIGHT_ADJ;
	}
}

void GoldBrick::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CMario *mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	vy += ay * dt;
	vx += ax * dt;

	if (y <= minY)
	{
		vy = GOLD_BRICK_SPEED_DOWN;
		if (mario->GetLevel() != MARIO_LEVEL_SMALL)
		{
			if (objType == GOLD_BRICK_COIN)
			{
				isBreak = true;
			}
		}
	}
	if (y > startY)
	{
		y = startY;
		vy = 0;
		if (mario->GetLevel() != MARIO_LEVEL_SMALL)
		{
			isEmpty = true;
			isUnbox = true;
		}
	}

	CPlayScene *scene = (CPlayScene *)CGame::GetInstance()->GetCurrentScene();

	if (isUnbox)
	{
		if (objType == GOLD_BRICK_MUSHROOM)
		{
			CMushroom *mushroom = new CMushroom(x, y);
			mushroom->SetState(MUSHROOM_STATE_UP);
			scene->objects.insert(scene->objects.begin() + 1, mushroom);
		}
		isUnbox = false;
	}

	if (isBreak)
	{
		isDeleted = true;
		isBreak = false;

		BreakBrick *break1 = new BreakBrick(x, y);
		break1->SetState(BREAK_STATE_TOP_RIGHT);
		BreakBrick *break2 = new BreakBrick(x, y);
		break2->SetState(BREAK_STATE_TOP_LEFT);
		BreakBrick *break3 = new BreakBrick(x, y);
		break3->SetState(BREAK_STATE_BOTTOM_RIGHT);
		BreakBrick *break4 = new BreakBrick(x, y);
		break4->SetState(BREAK_STATE_BOTTOM_LEFT);

		scene->objects.push_back(break1);
		scene->objects.push_back(break2);
		scene->objects.push_back(break3);
		scene->objects.push_back(break4);
	}

	if (mario->isActivePButton && objType == GOLD_BRICK_COIN)
	{
		this->SetState(GOLD_BRICK_STATE_TRANSFORM_COIN);
	}

	if (isTransform && GetTickCount64() - transform_start > GOLD_BRICK_COIN_TIME_OUT)
	{
		SetState(GOLD_BRICK_STATE_NORMAL);
		isTransform = false;
		mario->isActivePButton = false;
		isPress = false ;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void GoldBrick::SetBreak()
{

	if (objType == GOLD_BRICK_COIN && !isTransform && !isEmpty)
	{ // Chưa biến thành vàng
		isBreak = true;
	}
	else if (objType == GOLD_BRICK_P_BUTTON)
	{
		isEmpty = true;
	}
}

void GoldBrick::SetPress()
{
	if (objType == GOLD_BRICK_P_BUTTON && isEmpty)
	{
		CMario *mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
		mario->isActivePButton = true;
		isPress = true;
	}
}

void GoldBrick::Render()
{
	CMario *mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	int aniId = ID_ANI_GOLD_BRICK;

	if (objType == GOLD_BRICK_MUSHROOM)
	{
		if (isEmpty)
		{
			aniId = ID_ANI_GOLD_BRICK_EMPTY;
		}
	}
	else if (objType == GOLD_BRICK_P_BUTTON)
	{
		if (!isEmpty)
		{
			aniId = ID_ANI_GOLD_BRICK ;
		}
		else
		{
			if (mario->isActivePButton)
			{
				aniId = ID_ANI_PBUTTON_PRESSED;
			}
			else
			{
				aniId = ID_ANI_PBUTTON;
			}
		}
	}
	else
	{
		if (isTransform)
		{
			aniId = ID_ANI_COIN_IDLE;
		}
		else
		{
			aniId = ID_ANI_GOLD_BRICK;
		}
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	// RenderBoundingBox();
}

void GoldBrick::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void GoldBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOLD_BRICK_STATE_UP:
		vy = -GOLD_BRICK_SPEED_UP;
		break;
	case GOLD_BRICK_STATE_TRANSFORM_COIN:
		if (this->GetModel() == GOLDBRICK)
		{
			SetType(EType::COIN);
			transform_start = GetTickCount64();
			isTransform = true;
		}
		break;
	case GOLD_BRICK_STATE_NORMAL:
		if (this->GetModel() == COIN)
		{
			// DebugOut(L"[INFO] Brick State\n");
			SetType(EType::GOLDBRICK);
			transform_start = -1;
			isTransform = false;
		}
		break;
	}
}
