#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_JUMP_SPEED_MAX 0.28f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

//FIRE MARIO
#define ID_ANI_FIRE_MARIO_IDLE_RIGHT 2400
#define ID_ANI_FIRE_MARIO_IDLE_LEFT 2401

#define ID_ANI_FIRE_MARIO_WALKING_RIGHT 2500
#define ID_ANI_FIRE_MARIO_WALKING_LEFT 2501

#define ID_ANI_FIRE_MARIO_RUNNING_RIGHT 2600
#define ID_ANI_FIRE_MARIO_RUNNING_LEFT 2601

#define ID_ANI_FIRE_MARIO_JUMP_WALK_RIGHT 2700
#define ID_ANI_FIRE_MARIO_JUMP_WALK_LEFT 2701

#define ID_ANI_FIRE_MARIO_JUMP_RUN_RIGHT 2800
#define ID_ANI_FIRE_MARIO_JUMP_RUN_LEFT 2801

#define ID_ANI_FIRE_MARIO_SIT_RIGHT 2900
#define ID_ANI_FIRE_MARIO_SIT_LEFT 2901

#define ID_ANI_FIRE_MARIO_BRACE_RIGHT 2100
#define ID_ANI_FIRE_MARIO_BRACE_LEFT 2101

//RACOON MARIO
#define ID_ANI_RACOON_MARIO_IDLE_RIGHT 3400
#define ID_ANI_RACOON_MARIO_IDLE_LEFT 3401

#define ID_ANI_RACOON_MARIO_WALKING_RIGHT 3500
#define ID_ANI_RACOON_MARIO_WALKING_LEFT 3501

#define ID_ANI_RACOON_MARIO_RUNNING_RIGHT 3600
#define ID_ANI_RACOON_MARIO_RUNNING_LEFT 3601

#define ID_ANI_RACOON_MARIO_JUMP_WALK_RIGHT 3700
#define ID_ANI_RACOON_MARIO_JUMP_WALK_LEFT 3701

#define ID_ANI_RACOON_MARIO_JUMP_RUN_RIGHT 3800
#define ID_ANI_RACOON_MARIO_JUMP_RUN_LEFT 3801

#define ID_ANI_RACOON_MARIO_SIT_RIGHT 3900
#define ID_ANI_RACOON_MARIO_SIT_LEFT 3901

#define ID_ANI_RACOON_MARIO_BRACE_RIGHT 3100
#define ID_ANI_RACOON_MARIO_BRACE_LEFT 3101

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_FIRE	3
#define MARIO_LEVEL_RACOON	4

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_RACOON_BBOX_WIDTH  20

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define ADJUST_MARIO_COLLISION_WITH_COLOR_BLOCK 1
#define MARIO_UNTOUCHABLE_TIME 2500

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level; 
	int untouchable; 
	ULONGLONG untouchable_start;
	BOOLEAN isOnPlatform;
	int coin; 

	BOOLEAN isGoThroughBlock = false;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithBackgroundBlock(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdFire();
	int GetAniIdRacoon();

public:
	CMario(float x, float y) : CGameObject(x, y)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY; 

		level = MARIO_LEVEL_BIG;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void addCoin() {coin++ ;} ;
};