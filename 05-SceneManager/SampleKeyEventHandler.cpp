#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	// SAMPLE CODE GET MARIO OBJECT - QUICK SEARCH PURPOSE
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		// DebugOut(L"[INFO] mario->GetVx(): %f\n", mario->GetVx());
		if( mario->getLevel() == MARIO_LEVEL_RACOON && abs(mario->GetVx()) > MARIO_FLYING_CONDITION_SPEED) {
			mario->SetState(MARIO_STATE_FLY);
		}
		else {
			mario->SetState(MARIO_STATE_JUMP);
		}
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_RACOON);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_P:
		// DebugOut(L"[INFO] Mario state:  %d\n", mario->GetState());
		// DebugOut(L"[INFO] Mario y  %f\n", mario->GetY());
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		if(mario->GetStatus() == MARIO_STATUS_FLY) {
			mario->SetStatus(MARIO_STATUS_FALL) ;
			DebugOut(L"MARIO_STATE_RELEASE_FLY \n", mario->GetState()) ;
			mario->SetState(MARIO_STATE_RELEASE_FLY) ;
		}
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
			// DebugOut(L"MARIO_STATE_HOLD_RELEASE \n") ;
			// mario->SetState(MARIO_STATE_HOLD_RELEASE);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if(!mario ) return; 
	if (game->IsKeyDown(DIK_RIGHT))
	{
		mario->SetRorate() ;
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
		
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		mario->SetRorate() ;
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
		mario->SetState(MARIO_STATE_IDLE);
}