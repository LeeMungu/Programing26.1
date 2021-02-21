#pragma once
#include "Boom.h"
#include "Climb.h"
#include "Fall.h"
#include "Run.h"
#include "Stoper.h"
#include "Umbrella.h"
#include "Dig.h"

class Player;
class State
{
	Player* mPlayer;
public:
	virtual void Init() {}
	virtual void Release(){}
	virtual void Update(){}
	virtual void Render(HDC hdc){}

	void SetPlayerPtr(Player* player) { mPlayer = player; }
};

