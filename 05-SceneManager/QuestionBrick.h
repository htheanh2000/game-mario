#pragma once
#include "GameObject.h"

#define QUESTION_BRICK_BBOX_WIDTH 16
#define QUESTION_BRICK_BBOX_HEIGHT 16

#define ID_ANI_QUESTION_BRICK 102
#define ID_ANI_QUESTION_BRICK_EMPTY 103

#define COINS_EFFECT 1  
#define RED_MUSHROOM_OR_LEAF_EFFECT 2  
#define GREEN_MUSHROOM_EFFECT 3
class CQuestionBrick :
    public CGameObject
{   
public:
    BOOLEAN isEmpty = false;
    void activateEffect() ;
    
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Render();
    CQuestionBrick(float x, float y, int type) ;
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual int IsCollidable() { return 0; };
    virtual int IsBlocking() { return 1; };
};