﻿#pragma once
#include "GameObject.h"

#define KOOPAS_GREEN 1
#define KOOPAS_RED 2
#define KOOPAS_GREEN_WING 3

// KOOPAS GREEN
#define ID_ANI_KOOPAS_WALKING_RIGHT 40001
#define ID_ANI_KOOPAS_WALKING_LEFT 40002
#define ID_ANI_KOOPAS_DEFEND 40003
#define ID_ANI_KOOPAS_IS_KICKED 40004
#define ID_ANI_KOOPAS_IS_UPSIDE 40005
#define ID_ANI_KOOPAS_COMEBACK 40006
#define ID_ANI_KOOPAS_UPSIDE_ISKICKED 40007	// bị raccoon tấn công và bị đá
#define ID_ANI_KOOPAS_UPSIDE_COMEBACK 40008 // hiệu ứng bị lật úp và bắt đầu ra khỏi mai rùa
#define ID_ANI_KOOPAS_GREEN_WING_RIGHT 40009
#define ID_ANI_KOOPAS_GREEN_WING_LEFT 40010

// KOOPAS RED
#define ID_ANI_KOOPAS_RED_WALKING_RIGHT 40011
#define ID_ANI_KOOPAS_RED_WALKING_LEFT 40012
#define ID_ANI_KOOPAS_RED_DEFEND 40013
#define ID_ANI_KOOPAS_RED_IS_KICKED 40014
#define ID_ANI_KOOPAS_RED_IS_UPSIDE 40015
#define ID_ANI_KOOPAS_RED_COMEBACK 40016
#define ID_ANI_KOOPAS_RED_UPSIDE_ISKICKED 40017 // bị raccoon tấn công và bị đá
#define ID_ANI_KOOPAS_RED_UPSIDE_COMEBACK 40018 //bị lật úp và bắt đầu ra khỏi mai rùa

#define KOOPAS_GRAVITY 0.002f

#define KOOPAS_BBOX_WIDTH 14
#define KOOPAS_BBOX_HEIGHT 26

#define KOOPAS_WALKING_SPEED 0.02f
#define KOOPAS_IS_KICKED_SPEED 0.18f
#define KOOPAS_SPEED_Y_IS_FIRE_ATTACKED 0.4f
#define KOOPAS_SPEED_Y_IS_TAIL_ATTACKED 0.4f
#define KOOPAS_SPEED_X_IS_TAIL_ATTACKED 0.05f
#define KOOPAS_RED_WING_SPEED_X 0.03f

#define KOOPAS_WING_JUMP_SPEED 0.15f

#define KOOPAS_BBOX_HEIGHT_DEFEND 16
#define ADJUST_POSITION_KOOPAS_HELD 13
#define KOOPAS_COMBACK_HEIGHT_ADJUST 0.15f
#define KOOPAS_BOUNCE_SPEED 0.3f

#define KOOPAS_DEFEND_TIMEOUT 8000 // hết thời gian defend ( ra khỏi mai rùa và bắt đầu đi)
#define KOOPAS_COMBACK_START 6000 //thời gian tính từ lúc defend đến lúc có hiệu ứng comeback
#define KOOPAS_RESPAWN_START 4000 //thời gian tính từ lúc die đến lúc hồi sinh

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DEFEND 200
#define KOOPAS_STATE_IS_KICKED 300
#define KOOPAS_STATE_UPSIDE 400
#define KOOPAS_STATE_JUMP 500
#define KOOPAS_STATE_DIED 600

#define ADJUST_X_TO_RED_CHANGE_DIRECTION 10

#define KOOPAS_WING_GRAVITY 0.0002f
#define KOOPAS_COLLISION_LIMITATION 3 // Va chạm tối đa 3 lần thì sẽ bị delete
class Koopas :
    public CGameObject
{
protected:
	float ax;
	float ay;
	
	float respawn_pos_x;
	float respawn_pos_y;
	// vector<LPGAMEOBJECT> effects;
	int mario_nx;
	int collision_count = 0 ; // Đếm va chạm

public:
	Koopas(float x, float y, int model);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable();
	virtual int IsBlocking() { return isDied; }
	virtual void OnNoCollision(DWORD dt);

	BOOLEAN isTailAttacked = false;
	BOOLEAN isHeld;
	BOOLEAN isDefend;
	BOOLEAN isKicked;
	BOOLEAN isComeback;
	BOOLEAN isUpside;
	BOOLEAN isDied;

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);
	void OnCollisionWithBackGroundBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGoldBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);

	virtual void SetState(int state);

	ULONGLONG defend_start;
	ULONGLONG die_start;

};

