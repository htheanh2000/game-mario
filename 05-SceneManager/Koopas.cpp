#include "Koopas.h"
#include "Mario.h"
#include "QuestionBrick.h"
#include "BGBlock.h"

#include "Utils.h"
#include "SoftBrick.h"
#include "PlayScene.h"
#include "DirectionBrick.h"

Koopas::Koopas(float x, float y, int type) : CGameObject(x, y)
{
	initX = x;
	initY = y;
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	this->objType = type;
	state = KOOPAS_STATE_WALKING;
	this->vx = 0 ;
	if(type == KOOPAS_GREEN_WING) {
		hasWing = true;
	}
	this->jumpStart = GetTickCount64() + KOOPAS_JUMP_TIMESLEEP;

	
}



void Koopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	int bwidth = KOOPAS_BBOX_WIDTH ;
	int bheight = KOOPAS_BBOX_HEIGHT ;

	if(state == KOOPAS_STATE_DEFEND || state == KOOPAS_STATE_KICKED) {
		bheight = KOOPAS_DEFEND_BBOX_HEIGHT ; //Update the bounding box after chagne animation
	}

	if(state == KOOPAS_STATE_REPAWNING) {
		bheight = KOOPAS_RESPAWN_BBOX_HEIGHT ; //Update the bounding box after chagne animation
	}

	left = x - bwidth / 2;
	top = y - bheight / 2;
	right = left + bwidth;
	bottom = top + bheight;
}

void Koopas::kicked() {
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
	vx = KOOPAS_KICKED_SPEED * mario->getNx(); 
	this->SetState(KOOPAS_STATE_KICKED);
};

void Koopas::hold() { // Koopas is hold by mario
	this->SetState(KOOPAS_STATE_HOLD);
};

void Koopas::defend() { // Koopas is hold by mario
	this->SetState(KOOPAS_STATE_DEFEND);
	// if(this->state != KOOPAS_STATE_DEFEND) {
		this->defending_start = GetTickCount64();
	// }
};

void Koopas::TurnBack() {
	vx = -vx;
	// DebugOut(L"[INFO] Koopas DX %f\n", this->GetDX());
	linkedObj->SetPosition(this->GetX() , this->GetY());

};

void Koopas::Hit() {
	DebugOut(L"[INFO] objType  %d\n", objType);
	if(objType == KOOPAS_GREEN_WING && hasWing) {
		hasWing = false ;
	}
	else {
		this->defend();
	}
};

void Koopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if(vx == 0 ) {
		CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
		if(x - mario->GetX() < 160) {
			vx = -KOOPAS_SPEED ;
			if(objType == KOOPAS_GREEN_WING) {
				jumpStart = GetTickCount64();
				vx = - KOOPAS_WING_SPEED;
			}
		}
	}

	if(y >= 1000 && state != KOOPAS_STATE_DEAD) {
		// DebugOut(L"[INFO] KOOPAS_STATE_DEAD  ");
		state = KOOPAS_STATE_DEAD ;
		dead_start = GetTickCount64();
	}

	if(objType == KOOPAS_GREEN_WING && hasWing) {
		// handle koopas wing effct -> jump
		if(GetTickCount64() > jumpStart ) {
			// Koopas jump
			vy = -KOOPAS_JUMP_SPEED;
			// Reset next jump start
			jumpStart = GetTickCount64() + KOOPAS_JUMP_TIMESLEEP ;
		}
	}
	
	if(state == KOOPAS_STATE_DEFEND) {
		vx = 0;
	}

	if(state == KOOPAS_STATE_HOLD) {
		vx=0;
		vy=0;
		CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
		if(mario->GetState() == MARIO_STATE_HOLD_RELEASE ) {
			this->kicked();
		}
		else {
			this->SetPosition(mario->GetX() + mario->getMarioWidthSize() * mario->getNx(), mario->GetY() - KOOPAS_DEFEND_BBOX_HOLD_ADJUSTMENT);
		}
	}

	if((defending_start + KOOPAS_WAITING_RESPAWW_TIME < GetTickCount64()) && (state == KOOPAS_STATE_DEFEND)  ) {
		// Koopas repaws or change defend to walk state
		respawning_start = GetTickCount64();
		y = y - 1;
		this->SetState(KOOPAS_STATE_REPAWNING) ;
	}

	if(dead_start + KOOPAS_WAITING_RESPAWW_TIME < GetTickCount64() &&  state == KOOPAS_STATE_DEAD  ) {
		CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 
		if(objType == KOOPAS_GREEN_WING ) {  // Respawn swing 
			vx = -KOOPAS_WING_SPEED ;
			x = initX ;
			y = initY ;
			defend_colitions = 0;
			state = KOOPAS_STATE_WALKING ;
			hasWing = true ;
		}
		else if ( abs(mario->GetX() - initX) > 160) { // || only respawn when player go away
			vx = -KOOPAS_SPEED ; 
			x = initX ;
			y = initY ;
			defend_colitions = 0;
			state = KOOPAS_STATE_WALKING ;
		}
	}

	if(respawning_start + KOOPAS_WAITING_RESPAWWING_TIME < GetTickCount64() && state == KOOPAS_STATE_REPAWNING) {
		// Koopas repaws or change defend to walk state
		y = y - 10;
		vx = KOOPAS_SPEED ;
		this->SetState(KOOPAS_STATE_WALKING) ;
	}
	

	if(!linkedObj && this->state == KOOPAS_STATE_WALKING && objType != KOOPAS_GREEN_WING ) { // Should be on the ground first
		CPlayScene *scene = (CPlayScene *)CGame::GetInstance()->GetCurrentScene();
		CDirectionBrick *DBrick = new CDirectionBrick(this);
		scene->objects.push_back(DBrick);
		linkedObj = DBrick ;
	}
	else {
		// Delete the object
	}

	if(unTouchable == true) {
		x += this->GetDX() ; // Update x postion by +- 1 
		y -= 1;
		unTouchable = false;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
	
}

void Koopas::Render()
{
	int aniId = ID_ANI_KOOPAS_WALKING_RIGHT;

	if (objType == KOOPAS_GREEN_WING) {
		if(hasWing) {
			if (vx > 0) {
			aniId = ID_ANI_KOOPAS_GREEN_WING_RIGHT;
			}
			else {
				aniId = ID_ANI_KOOPAS_GREEN_WING_LEFT;
			}
		}
		else {
			if (vx > 0) {
			aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
			}
			else {
				aniId = ID_ANI_KOOPAS_WALKING_LEFT;
			}
		}
		
	}

	if (objType == KOOPAS_GREEN) {
		if (vx > 0) {
			aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
		}
		else {
			aniId = ID_ANI_KOOPAS_WALKING_LEFT;
		}
	}

	if (state == KOOPAS_STATE_DEFEND ) {
		aniId = ID_ANI_KOOPAS_DEFEND ;
	}

	if (state == KOOPAS_STATE_HOLD ) {
		aniId = ID_ANI_KOOPAS_DEFEND ;
	}

	if (state == KOOPAS_STATE_KICKED) {
		aniId = ID_ANI_KOOPAS_IS_KICKED;
	}

	if (state == KOOPAS_STATE_REPAWNING) {
		aniId = ID_ANI_KOOPAS_GREEN_RESPAWNING;
	}

	if(state == KOOPAS_STATE_DEAD) {
		return ; // Dead shoud return nothing
	} 	
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	// RenderBoundingBox();

}


int Koopas::IsCollidable()
{
    return 1;
}

void Koopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void Koopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return; 
	if (dynamic_cast<Koopas*>(e->obj)) {
		unTouchable = true;
		return;
	}
	else if (dynamic_cast<CQuestionBrick*>(e->obj)) {
		CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj);
		questionBrick->activateEffect();
		// this->isDeleted = true;
	} 
	else  if (dynamic_cast<SoftBrick*>(e->obj) && state == KOOPAS_STATE_KICKED) {
		SoftBrick* softbrick = dynamic_cast<SoftBrick*>(e->obj);
		softbrick->Delete();
		defend_colitions--; //Make it break alll soft brick
	} ;

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
		if(defend_colitions <= KOOPAS_DEFEND_MAX_COLLISION) { // lmit maximal colition
			defend_colitions++;
		}
		else {
			dead_start = GetTickCount64();
			state = KOOPAS_STATE_DEAD;
		}
	}

	
}





