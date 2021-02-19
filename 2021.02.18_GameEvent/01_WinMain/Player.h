#pragma once
#include "GameObject.h"

class GameObject;
class Player : public GameObject
{

	enum class CharactorState : int
	{
		RightIdle = 0,
		LeftIdle = 1,
		RightRun = 2,
		LeftRun = 3,
		RightAttack = 4,
		LeftAttack = 5,
		End
	};

	CharactorState mState;

	class Weapon* mWeapon;
	Player* mPlayer;
	vector<GameObject*> mEnemyList;

	int mHpPoint;

	class Image* mImage;
	class Image* mAttackImage;
	class Animation* mIdleAnimation;
	class Animation* mLeftIdleAnimation;
	class Animation* mRunAnimation;
	class Animation* mLeftRunAnimation;
	class Animation* mAttackAnimation;
	class Animation* mLeftAttackAnimation;
	class Animation* mCurrentAnimation;	//���� �ִϸ��̼�

	bool mIsStop;
public:
	Player(const string& name,float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	float GetX() { return mX; }
	float GetY() { return mY; }
	
	void GetXPosition(int X) { mX += X; }
	void SetHpPoint(int X) { mHpPoint -= X; }

	int GetHpPoint() { return mHpPoint; }

	bool GetStop() const { return mIsStop; }
	void SetStop(bool isStop) { mIsStop = isStop; }

};

