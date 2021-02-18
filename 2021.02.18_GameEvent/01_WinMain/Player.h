#pragma once
#include "GameObject.h"
class Player : public GameObject
{
	class Image* mImage;
	class Image* mAttackImage;
	class Animation* mIdleAnimation;
	class Animation* mRunAnimation;
	class Animation* mLeftRunAnimation;
	class Animation* mAttackAnimation;
	class Animation* mCurrentAnimation;	//���� �ִϸ��̼�
public:
	Player(const string& name,float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	float GetX() { return mX; }
	float GetY() { return mY; }
};

