#pragma once
#include "GameObject.h"
enum class PlayerState
{

};

class GameObject;
class Image;
class State;
class Animation;
class Player : public GameObject
{
	Image* mImage;

	State* mCurrentState;
	State* mBoomState;
	State* mClimbState;
	State* mStopperState;
	State* mUmbrellaState;
	State* mDigState;
	State* mFallState;
	State* mRunState;
	
	PlayerState mPlayerState;

	Animation* mCurrentAnimation;
	//오른쪽 왼쪽 구분하는 변수 0이면 오른쪽 1이면 왼쪽
	int mIsMotionRL;
	float mSpeed;
	float mGravity;

public:
	Player(const string& name,float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	float GetX() { return mX; }
	float GetY() { return mY; }
	
	void GetXPosition(int X) { mX += X; }
	
	int GetIntMotionRL()const { return mIsMotionRL; }
	void SetState(int intMotionRL) { mIsMotionRL = intMotionRL; }

	State* GetState()const { return mCurrentState; }
	void SetState(State* state) { mCurrentState = state; }

	float GetSpeed()const { return mSpeed; }
	void SetSpeed(float speed){ mSpeed = speed; }
	
	float GetGravity()const { return mGravity; }
	void SetGravity(float gravity) { mGravity = gravity; }
};

