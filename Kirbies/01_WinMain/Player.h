#pragma once
#include "GameObject.h"

class GameObject;
class Image;
class State;
class Animation;
class Player : public GameObject
{
	Image* mImage;
	State* mState;
	Animation* mCurrentAnimation;
	//������ ���� �����ϴ� ���� 0�̸� ������ 1�̸� ����
	int mIsMotionRL;
public:
	Player(const string& name,float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	float GetX() { return mX; }
	float GetY() { return mY; }
	
	void GetXPosition(int X) { mX += X; }
	
	int GetIntMotionRL()const { return mIntMotionRL; }
	void SetState(int intMotionRL) { mIntMotionRL = intMotionRL; }

	State* GetState()const { return mState; }
	void SetState(State* state) { mState = state; }
};

