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
#define ID_ANI_KOOPAS_GREEN_RESPAWNING 40019

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
#define KOOPAS_SPEED 0.02f
#define KOOPAS_WING_SPEED 0.03f
#define KOOPAS_JUMP_SPEED 0.2f
#define KOOPAS_KICKED_SPEED  0.2f

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 26
#define KOOPAS_DEFEND_BBOX_HEIGHT 16
#define KOOPAS_RESPAWN_BBOX_HEIGHT 18


#define KOOPAS_DEFEND_BBOX_HOLD_ADJUSTMENT 2
#define KOOPAS_WAITING_RESPAWW_TIME  5000 
#define KOOPAS_WAITING_RESPAWWING_TIME 2500 // Preparing for spawnng
#define KOOPAS_JUMP_TIMESLEEP 1000



//--------------------STATE -------------------------
#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DEFEND 200
#define KOOPAS_STATE_KICKED 300
#define KOOPAS_STATE_HOLD 400
#define KOOPAS_STATE_REPAWNING 500
#define KOOPAS_STATE_DEAD 600
#define KOOPAS_STATE_WING_WALKING 700

#define KOOPAS_DEFEND_MAX_COLLISION 3
class Koopas :
    public CGameObject
{

private:
protected:

	float initX;
	float initY;
	float ax;
	float ay;
    int objType;
	int defend_colitions =  0;
	BOOLEAN  hasWing = false; // FOr wing koopas only 

	CGameObject* linkedObj ;
	ULONGLONG jumpStart = 0 ;
	vector<LPGAMEOBJECT> effects;
	ULONGLONG defending_start = 0;
	ULONGLONG respawning_start = 0;
	ULONGLONG dead_start = 0;


public:
	Koopas(float x, float y, int type);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable();
	virtual int IsBlocking() { return 1; }
	virtual void OnNoCollision(DWORD dt);
	virtual void OnCollisionWith(LPCOLLISIONEVENT e) ;
	virtual void kicked() ;
	virtual void hold() ;
	virtual void defend() ;
	virtual void TurnBack() ;
	virtual void Hit() ; // Hit by Mario
};

