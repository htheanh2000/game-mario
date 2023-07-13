#pragma once
#include "Mario.h"

#define ID_ANI_HUD 30012
#define HUD_HEIGHT 32
#define HUD_WIDTH 272

class HUD
{
	float x, y;
public:
	HUD(float x, float y);
	void Render(CMario* mario, int remainingTime);
};

