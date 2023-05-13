#include "FireBall.h"

FireBall::FireBall(float x, float y) :CGameObject(x, y)
{
	this->x = x;
	this->y = y;
	this->ax = 0;
	this->ay = FIRE_BALL_GRAVITY;
	vx = -GOOMBA_WALKING_SPEED;
}

FireBall::FireBall(float x, float y, float tx, float ty) :CGameObject(x, y)
{
	// DebugOut(L"[INFO] FireBall x  %f\n", x);
	// DebugOut(L"[INFO] FireBall y  %f\n", y);
	// DebugOut(L"[INFO] FireBall tx  %f\n", tx);
	// DebugOut(L"[INFO] FireBall ty  %f\n", ty);

	this->x = x;
	this->y = y;
	
	this->tx = tx;
	this->ty = ty;
	
	float dx = tx - x;  // Calculate the difference in x-coordinates
    float dy = ty - y;  // Calculate the difference in y-coordinates

    float distance = sqrt(dx * dx + dy * dy);  // Calculate the distance between the current position and the target

    // Calculate the normalized velocity vector
    this->vx = dx / distance * FIRE_BALL_SPEED;
    this->vy = dy / distance * FIRE_BALL_SPEED;
	// DebugOut(L"[INFO] FireBall vx  %f\n", vx);
	// DebugOut(L"[INFO] FireBall vy  %f\n", vy);
}

void FireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIRE_BALL_BBOX_WIDTH / 2;
	top = y - FIRE_BALL_BBOX_HEIGHT / 2;
	right = left + FIRE_BALL_BBOX_WIDTH;
	bottom = top + FIRE_BALL_BBOX_HEIGHT;
}

void FireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void FireBall::Render()
{
	int aniId = FIREBALL_ANI;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	// RenderBoundingBox();
}

void FireBall::OnNoCollision(DWORD dt)
{
	// DebugOut(L"[INFO] x  %f\n", x);
	// DebugOut(L"[INFO] y  %f\n", y);
	x += vx * dt;
	y += vy * dt;
}

void FireBall::OnCollisionWith(LPCOLLISIONEVENT e)
{
	this->isDeleted = true;
}

