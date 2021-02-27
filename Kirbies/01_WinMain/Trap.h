#pragma once
#include "GameObject.h"
#include "Player.h"
class Trap : public GameObject
{
	PlayerState mState;

public:
	Trap(const string& name, float x, float y, float sizeX, float sizeY, PlayerState state);

	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};

