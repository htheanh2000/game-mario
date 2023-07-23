#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "QuestionBrick.h"
#include "Collision.h"
#include "BGBlock.h"
#include "MushRoom.h"
#include "Koopas.h"
#include "Leaf.h"
#include "FireBall.h"
#include "PiranhaPlant.h"
#include "PButton.h"
#include "SoftBrick.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if (lifeCount == 0)
	{
		// DebugOut(L">>> Mario DIE >>> \n");
		// SetState(MARIO_STATE_DIE);
		// TODO: Back to world map
	}

	if(die_start + 1000 < GetTickCount64() && state == MARIO_STATE_DIE) {
		CGame::GetInstance()->InitiateSwitchScene(WORLD_DMAP_ID);
	}

	// DebugOut(L"[INFO] Mario status:  %d\n", isFlatMario);

	if (abs(vx) > abs(maxVx))
		vx = maxVx;

	if (this->status == MARIO_STATE_FLY && vy > maxVy) {
		vy = maxVy; 
	}

	if (this->status == MARIO_STATE_FLY && vy < minVy) {
		vy = minVy;
	}

	if(isAttacking) {
		vx = 0 ; // Mario should idle
	}

	if(attackTime + MARIO_ATTACK_TIME < GetTickCount64()) {
		isAttacking = false ; // Finish attack
	}

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	isOnPlatform = false;

	if (isGoThroughBlock && !isFlatMario)
	{
		// reset y to avoid mario lag and stuck in block
		// To do: Fix mario can jump higher when in block
		y -= ADJUST_MARIO_COLLISION_WITH_COLOR_BLOCK;
		vy = -MARIO_JUMP_SPEED_MAX;
		isGoThroughBlock = false;
	}

	CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;

	if (y <  -100) {
		y = -100;
	}
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{

	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) {
			// status = MARIO_STATUS_DEFAULT;
			isOnPlatform = true;
		}
	}
	else if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba *>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin *>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal *>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CBGBlock *>(e->obj))
		OnCollisionWithBackgroundBlock(e);
	else if (dynamic_cast<CQuestionBrick *>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CMushroom *>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<Koopas *>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CLeaf *>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<CLeaf *>(e->obj))
		OnCollisionWithLeaf(e);
	else if (dynamic_cast<FireBall *>(e->obj)) 
		this->Hit();
	else if (dynamic_cast<PiranhaPlant *>(e->obj)) 
		this->Hit();
	else if (dynamic_cast<PButton *>(e->obj)) 
		OnCollisionWithButton(e);
	else if (dynamic_cast<SoftBrick *>(e->obj) && this->pressedButton) 
		OnCollisionWithCoin(e);
}

void CMario::OnCollisionWithSoftBrick(LPCOLLISIONEVENT e)
{
	
}

void CMario::OnCollisionWithButton(LPCOLLISIONEVENT e)
{
	PButton *btn = dynamic_cast<PButton *>(e->obj);
	// DebugOut(L"[INFO] OnCollisionWith mario %f\n", 1 );
	if(isAttacking) {
		btn->SetState(STATE_BREAK);
	}
	else if (e->ny < 0 && btn->state == STATE_BREAK) {
		btn->SetState(STATE_JUMPED_ON);
		btn->jumpedOn = 1;
		pressedButton = true;
	}
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	SetLevel(MARIO_LEVEL_RACOON);
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	Koopas *koopas = dynamic_cast<Koopas *>(e->obj);
	
	// isAttacking && level == MARIO_LEVEL_RACOON
	// jump on top >> kill Koopas and deflect a bit
	if (e->ny < 0)
	{
		if(koopas->GetState() == KOOPAS_STATE_WALKING) {
			koopas->Hit();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopas->GetState() == KOOPAS_STATE_DEFEND) {
			koopas->kicked(); 
		}
		else {
			this->Hit() ;
		}
	}
	else // hit by Koopas
	{
		if(this->getLevel() == MARIO_LEVEL_RACOON) {
			// Attack Koopas
			
		}
		if (koopas->GetState() == KOOPAS_STATE_DEFEND)
		{
			if (this->GetState() == MARIO_STATE_RUNNING_RIGHT || this->GetState() == MARIO_STATE_RUNNING_LEFT) 
			{
				koopas->hold();
				isHold = true ;
			}
			else {
				koopas->kicked(); 
			}
			
		}
		else {
			this->Hit() ;
		}
	}
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	CMushroom *mushroom = dynamic_cast<CMushroom *>(e->obj);
	if (mushroom->objType == RED_MUSHROOM)
	{
		// handle logic for red mushrooms -> upgrade mario level
		if (level == MARIO_LEVEL_RACOON)
		{
			// TODO: handle logic for raccoon level
		}
		else
		{
			SetLevel(MARIO_LEVEL_BIG);
		}
	}
	else if (mushroom->objType == GREEN_MUSHROOM)
	{
		// handle logic for green mushroom -> add 1 life score mario level
		setLifeCount(lifeCount + 1);
	}
	e->obj->Delete();
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

	// jump on top || mario racoon attack >> kill Goomba and deflect a bit
	if (e->ny < 0 || (isAttacking && level == MARIO_LEVEL_RACOON))
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->Hit();
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		this->Hit();
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal *p = (CPortal *)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithBackgroundBlock(LPCOLLISIONEVENT e)
{
	CBGBlock *block = dynamic_cast<CBGBlock *>(e->obj);
	if (e->ny > 0)
	{
		isGoThroughBlock = true;
	}
	if (block->objType == ENEMIES_ONLY_BLOCK)
	{
		isGoThroughBlock = true;
	}
}

void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e)
{
	if(e->ny > 0) { //go up
		CQuestionBrick *questionBrick = dynamic_cast<CQuestionBrick *>(e->obj);
		questionBrick->activateEffect();
	}
}
//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else if (isSitting)
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_SIT_RIGHT;
		else
			aniId = ID_ANI_MARIO_SIT_LEFT;
	}
	else if (vx == 0)
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
		else
			aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
	}
	else if (vx > 0)
	{
		if (ax < 0)
			aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
		else if (ax == MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
		else if (ax == MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
	}
	else // vx < 0
	{
		if (ax > 0)
			aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
		else if (ax == -MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
		else if (ax == -MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
	}

	if (aniId == -1)
		aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}

//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else if (isSitting)
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_SIT_RIGHT;
		else
			aniId = ID_ANI_MARIO_SIT_LEFT;
	}
	else if (vx == 0)
	{
		if (nx > 0)
			aniId = ID_ANI_MARIO_IDLE_RIGHT;
		else
			aniId = ID_ANI_MARIO_IDLE_LEFT;
	}
	else if (vx > 0)
	{
		if (ax < 0)
			aniId = ID_ANI_MARIO_BRACE_RIGHT;
		else if (ax == MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_MARIO_RUNNING_RIGHT;
		else if (ax == MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_WALKING_RIGHT;
	}
	else // vx < 0
	{
		if (ax > 0)
			aniId = ID_ANI_MARIO_BRACE_LEFT;
		else if (ax == -MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_MARIO_RUNNING_LEFT;
		else if (ax == -MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_MARIO_WALKING_LEFT;
	}

	if (aniId == -1)
		aniId = ID_ANI_MARIO_IDLE_RIGHT;
	return aniId;
}


//
// Get animation ID for Raccoon Mario
//
int CMario::GetAniIdRacoon()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X && abs(vx) >= MARIO_FLYING_CONDITION_SPEED)
		{
			if (nx >= 0)
				aniId = ID_ANI_RACOON_MARIO_FLYING_RIGHT; // FLying animation
			else
				aniId = ID_ANI_RACOON_MARIO_FLYING_LEFT; // FLying animation
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_RACOON_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_RACOON_MARIO_JUMP_WALK_LEFT;
		}
	}
	else if (isSitting)
	{
		if (nx > 0)
			aniId = ID_ANI_RACOON_MARIO_SIT_RIGHT;
		else
			aniId = ID_ANI_RACOON_MARIO_SIT_LEFT;
	}
	else if (vx == 0)
	{
		if (nx > 0)
			aniId = ID_ANI_RACOON_MARIO_IDLE_RIGHT;
		else
			aniId = ID_ANI_RACOON_MARIO_IDLE_LEFT;
	}
	else if (vx > 0)
	{
		if (ax < 0)
			aniId = ID_ANI_RACOON_MARIO_BRACE_RIGHT;
		else if (ax == MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_RACOON_MARIO_RUNNING_RIGHT;
		else if (ax == MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_RACOON_MARIO_WALKING_RIGHT;
	}
	else // vx < 0
	{
		if (ax > 0)
			aniId = ID_ANI_RACOON_MARIO_BRACE_LEFT;
		else if (ax == -MARIO_ACCEL_RUN_X)
			aniId = ID_ANI_RACOON_MARIO_RUNNING_LEFT;
		else if (ax == -MARIO_ACCEL_WALK_X)
			aniId = ID_ANI_RACOON_MARIO_WALKING_LEFT;
	}

	if(isAttacking) {
		DebugOut(L"[INFO] MARIO_STATUS_ATTACK:  %d\n", 1);
		if(ax < 0) {
			aniId = ID_ANI_RACOON_MARIO_ATTACK_LEFT;
		}
		else {
			aniId = ID_ANI_RACOON_MARIO_ATTACK_RIGHT;
		}
	}

	if (aniId == -1)
		aniId = ID_ANI_MARIO_IDLE_RIGHT;
	return aniId;
}

void CMario::Render()
{
	CAnimations *animations = CAnimations::GetInstance();
	int aniId = -1;

	if(isFlatMario){
		aniId = ID_ANI_MARIO_FLAT;	
	}
	else if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACOON)
		aniId = GetAniIdRacoon();

	animations->Get(aniId)->Render(x, y);

	// RenderBoundingBox();

	// DebugOutTitle(L"Coins: %d", coin);

	DebugOutTitle(L"Coins: %d, Score: %d, Life: %.2f", coin, score, lifeCount);
}

void CMario::SetRorate() {
	rotating = true;
}

void CMario::Die() {
	vx = 0;
	ax = 0;
	vy = -MARIO_JUMP_SPEED_Y ;
	state = MARIO_STATE_DIE ;
	die_start = GetTickCount64();
}

void CMario::Hit() {
	if (untouchable == 0)
		{
			ax = 0;
			vx = 0;
			this->state = MARIO_STATE_IDLE;
			if (level == MARIO_LEVEL_RACOON)
			{
				level = MARIO_LEVEL_BIG;
			}
			else if (level == MARIO_LEVEL_BIG)
			{
				level = MARIO_LEVEL_SMALL;
			}
			else if (level == MARIO_LEVEL_SMALL) {
				this->Die() ;
			}
			
			StartUntouchable();
	}
}

void CMario::Attack() {
	this->isAttacking = true;
	attackTime = GetTickCount64() ;
}


void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed!
	if (this->state == MARIO_STATE_DIE )
		return;

	switch (state)
	{
	case MARIO_STATE_MOVE_UP:
		ay = 0;
		ax = 0;
		vy = -FLAT_MARIO_SPEED ;
		vx = 0 ;
		break;
	case MARIO_STATE_MOVE_DOWN:
		ay = 0;
		ax = 0;
		vy = FLAT_MARIO_SPEED ;
		vx = 0 ;
		break;
	case MARIO_STATE_MOVE_RIGHT:
		ay = 0;
		ax = 0;
		vx = FLAT_MARIO_SPEED ;
		vy = 0 ;
		nx = 1;
		break;
	case MARIO_STATE_MOVE_LEFT:
		ay = 0;
		ax = 0;
		vx = -FLAT_MARIO_SPEED ;
		vy = 0 ;
		nx = -1;
		break;
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting)
			break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting)
			break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting)
			break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting)
			break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:

		if (isSitting)
			break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0)
			vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_FLY:
		DebugOut(L"MARIO_STATE_FLY \n");
		vy = -MARIO_FLY_SPEED_Y;
		status = MARIO_STATUS_FLY;
		ay = 0;
		break;

	case MARIO_STATE_RELEASE_FLY:
		ay = MARIO_GRAVITY;
		DebugOut(L"MARIO_STATE_RELEASE_FLY \n");
		if(this->GetDX() > 0) {
			this->SetState(MARIO_STATE_WALKING_RIGHT);
		}
		else {
			this->SetState(MARIO_STATE_WALKING_LEFT);
		}
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0;
			vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		if(! this->IsFlatMario()) {
			ax = 0.0f;
			vx = 0.0f;
			ay = MARIO_GRAVITY;
		}
		
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	
	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level >= MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			if (level == MARIO_LEVEL_RACOON)
			{
				left = x - MARIO_RACOON_BBOX_WIDTH / 2;
				right = left + MARIO_RACOON_BBOX_WIDTH;
			}
			else
			{
				left = x - MARIO_BIG_BBOX_WIDTH / 2;
				right = left + MARIO_BIG_BBOX_WIDTH;
			}
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

int CMario::getMarioWidthSize()
{
	if (level >= MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			return MARIO_BIG_SITTING_BBOX_WIDTH;
		}
		else
		{
			if (level == MARIO_LEVEL_RACOON)
			{
				return MARIO_RACOON_BBOX_WIDTH;
			}
			else
			{
				return MARIO_BIG_BBOX_WIDTH;
			}
		}
	}
	else
	{
		return MARIO_SMALL_BBOX_WIDTH;
	}
}

void CMario::SetLevel(int l)
{
	if(!this) return ;
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	if (this->level == MARIO_LEVEL_RACOON)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}
