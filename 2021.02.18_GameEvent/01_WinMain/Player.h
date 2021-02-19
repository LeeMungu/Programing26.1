#pragma once
#include "GameObject.h"
class Player : public GameObject
{

	enum class CharactorState : int
	{
		Idle = 0,
		LeftIdle = 1,
		Run = 2,
		LeftRun = 3,
		Attack = 4,
		LeftAttack = 5,
		End
	};

	CharactorState mState;


	Player* mPlayer;
	int mHpPoint;

	class Image* mImage;
	class Image* mAttackImage;
	class Animation* mIdleAnimation;
	class Animation* mLeftIdleAnimation;
	class Animation* mRunAnimation;
	class Animation* mLeftRunAnimation;
	class Animation* mAttackAnimation;
	class Animation* mLeftAttackAnimation;
	class Animation* mCurrentAnimation;	//현재 애니메이션
public:
	Player(const string& name,float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	float GetX() { return mX; }
	float GetY() { return mY; }
	
	
	int GetHpPoint() { return mHpPoint; }

};

