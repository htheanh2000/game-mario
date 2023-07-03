#pragma once
#include "GameObject.h"

// Define Koopas type
#define KOOPAS_GREEN 1
#define KOOPAS_RED 2
#define KOOPAS_GREEN_WING 3 // KOOPAS_PARATROOPA

// Koopas description 

//Koopa Paratroopa: A Koopa Troopa with wings. Green ones (which appear blue-green underground and in castles) jump towards the player or 
//fly back and forth, while red ones fly up and down.

//Koopa Troopa: A soldier of the Turtle Empire that marches onwards. If stomped, it retreats in its shell, which can be kicked to hit other 
//enemies and gain points. Green ones (which appear blue-green underground and in castles) walk back and forth just like Little Goombas, and red ones turn around when they find a pit.

// KOOPAS GREEN
#define ID_ANI_KOOPAS_WALKING_RIGHT 40001
#define ID_ANI_KOOPAS_WALKING_LEFT 40002
#define ID_ANI_KOOPAS_DEFEND 40003
#define ID_ANI_KOOPAS_IS_KICKED 40004
#define ID_ANI_KOOPAS_IS_UPSIDE 40005
#define ID_ANI_KOOPAS_COMEBACK 40006
#define ID_ANI_KOOPAS_UPSIDE_ISKICKED 40007	
#define ID_ANI_KOOPAS_UPSIDE_COMEBACK 40008 
#define ID_ANI_KOOPAS_GREEN_WING_RIGHT 40009
#define ID_ANI_KOOPAS_GREEN_WING_LEFT 40010

// KOOPAS RED
#define ID_ANI_KOOPAS_RED_WALKING_RIGHT 40011
#define ID_ANI_KOOPAS_RED_WALKING_LEFT 40012
#define ID_ANI_KOOPAS_RED_DEFEND 40013
#define ID_ANI_KOOPAS_RED_IS_KICKED 40014
#define ID_ANI_KOOPAS_RED_IS_UPSIDE 40015
#define ID_ANI_KOOPAS_RED_COMEBACK 40016
#define ID_ANI_KOOPAS_RED_UPSIDE_ISKICKED 40017 
#define ID_ANI_KOOPAS_RED_UPSIDE_COMEBACK 40018 

#define KOOPAS_GRAVITY 0.001f
#define KOOPAS_SPEED 0.01f
#define KOOPAS_JUMP_SPEED 0.3f
#define KOOPAS_KICKED_SPEED  0.2f

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_DEFEND_BBOX_HEIGHT 16


#define KOOPAS_DEFEND_BBOX_HOLD_ADJUSTMENT 2



//--------------------STATE -------------------------
#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DEFEND 200
#define KOOPAS_STATE_KICKED 300
#define KOOPAS_STATE_HOLD 400

#define KOOPAS_JUMP_TIMESLEEP 1000
class Koopas :
    public CGameObject
{

private:
protected:
	float ax;
	float ay;
    int objType;
	int dkicked = 1 ; // vector when mario kick off
	ULONGLONG jumpStart = 0 ;
	vector<LPGAMEOBJECT> effects;

public:
	Koopas(float x, float y, int type);
	Koopas(float x, float y, int type, int delay); // Init wing koopas


	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable();
	virtual int IsBlocking() { return 1; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) ;
	virtual void kicked() ;
	virtual void hold() ;
};

