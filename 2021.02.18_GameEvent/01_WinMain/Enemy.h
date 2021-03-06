#pragma once
#include "GameObject.h"

class Image;
class Animation;
class Player;
class Enemy : public GameObject
{
	Image* mImage;
	Animation* mIdleAnimation;
	Animation* mRunAnimation;
	Animation* mAttackAnimation;
	Animation* mCurrentAnimation;

	Player* mPlayer;
	int mHpPoint;
	int mDistance;
	float mDamage;
	float mSpeed;
	bool mIsFollow;

public:
	Enemy(const string& name, float x, float y);


	void SetPlayerPtr(Player* player) { mPlayer = player; }

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void HPCount(int x)//HP����
	{
		mHpPoint -= x;
	}
	float GetDamege() { return mDamage; }


};


