#pragma once
#include "GameObject.h"

class Player;

class Weapon : public GameObject
{


	Player* mPlayer;
	class Animation* mIdleAnimation;
	class Animation* mRunAnimation;
	class Animation* mCurrentAnimation;


public:
	Weapon(const string& name, float x, float y);
	void SetPlayerPtr(Player* player) { mPlayer = player; }

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void Attack(float mX, float mY, float sizeX, float sizeY);

};