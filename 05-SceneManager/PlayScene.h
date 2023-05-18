#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Map.h"
#include "BGBlock.h"
#include "Koopas.h"

#define MARIO_FIX_CAM_ADJUSTMENT 150

class CPlayScene: public CScene
{
protected: 
	// A play scene has to have player, right? 
	CMario* player = NULL;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILEMAP(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void SetCam(float cx, float cy);

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
	Map* map = NULL;

	vector<LPGAMEOBJECT> objects; // To handle effect brick (coins, magic , ...)
};

typedef CPlayScene* LPPLAYSCENE;

