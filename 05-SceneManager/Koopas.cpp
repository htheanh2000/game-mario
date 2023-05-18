#include "Koopas.h"
#include "Mario.h"
#include "QuestionBrick.h"
#include "BGBlock.h"

#include "Utils.h"
#include "SoftBrick.h"

Koopas::Koopas(float x, float y, int type) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	this->objType = type;
	state = KOOPAS_STATE_WALKING;
	this->vx = -KOOPAS_SPEED;
	this->jumpStart = GetTickCount64() + KOOPAS_JUMP_TIMESLEEP;
}

Koopas::Koopas(float x, float y, int type, int delay) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	this->objType = type;
	this->vx = -KOOPAS_SPEED;
	this->jumpStart = GetTickCount64() + KOOPAS_JUMP_TIMESLEEP + delay;
}

void Koopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	int bwidth = KOOPAS_BBOX_WIDTH ;
	int bheight = KOOPAS_BBOX_HEIGHT ;

	if(state == KOOPAS_STATE_DEFEND || state == KOOPAS_STATE_KICKED) {
		bheight = KOOPAS_DEFEND_BBOX_HEIGHT ; //Update the bounding box after chagne animation
	}

	left = x - bwidth / 2;
	top = y - bheight / 2;
	right = left + bwidth;
	bottom = top + bheight;
}

void Koopas::setDKicked(int vector) {
	this->dkicked = vector;
};



void Koopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if(objType == KOOPAS_GREEN_WING) {
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

	if(state == KOOPAS_STATE_KICKED) {
		vx = -KOOPAS_KICKED_SPEED * dkicked; 
	}
	

	CGameObject::Update(dt, coObjects);

		if( this->state == KOOPAS_STATE_KICKED ) {
		vector<LPGAMEOBJECT>* objects = new vector<LPGAMEOBJECT>();
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			LPGAMEOBJECT obj = (*coObjects)[i];
			if (obj->IsMarioBlocking() ) {
				objects->push_back(obj);
			}
		}
		CCollision::GetInstance()->Process(this, dt, objects);

		// clean up the memory after you're done using it
		delete objects;
	}
	else {
		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
	
}

void Koopas::Render()
{
	int aniId = ID_ANI_KOOPAS_WALKING_RIGHT;

	if (objType == KOOPAS_GREEN_WING) {
		if (vx > 0) {
			aniId = ID_ANI_KOOPAS_GREEN_WING_RIGHT;
		}
		else {
			aniId = ID_ANI_KOOPAS_GREEN_WING_LEFT;
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

	if (state == KOOPAS_STATE_DEFEND || state == KOOPAS_STATE_KICKED) {
		aniId = ID_ANI_KOOPAS_DEFEND ;
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
	if (dynamic_cast<Koopas*>(e->obj)) return; 

	if (dynamic_cast<CQuestionBrick*>(e->obj)) {
		CQuestionBrick* questionBrick = dynamic_cast<CQuestionBrick*>(e->obj);
		questionBrick->activateEffect();
		this->isDeleted = true;
	} ;

	if (dynamic_cast<SoftBrick*>(e->obj) && state == KOOPAS_STATE_KICKED) {
		SoftBrick* softbrick = dynamic_cast<SoftBrick*>(e->obj);
		softbrick->Delete();
		dkicked = -dkicked ;
	} ;

	if (e->ny != 0 )
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
	 
	
}

