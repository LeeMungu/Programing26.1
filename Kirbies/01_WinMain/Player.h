#pragma once
#include "GameObject.h"
enum class PlayerState
{
	CurrentState,
	BoomState,
	ClimbState,
	StopperState,
	UmbrellaState,
	DigState,
	FallState,
	RunState,
	TrapDieState,
	Empty
};

class GameObject;
class Image;
class State;
class Animation;
class Player : public GameObject
{
	Image* mImage;

	State* mCurrentState;
	//State* mBoomState;
	//State* mClimbState;
	//State* mStopperState;
	//State* mUmbrellaState;
	//State* mDigState;
	//State* mFallState;
	//State* mRunState;
	
	PlayerState mPlayerState;

	Animation* mCurrentAnimation;

	bool mIsGoal;
	bool mIsDoor;
	bool mIsChange;
	//오른쪽 왼쪽 구분하는 변수 0이면 오른쪽 1이면 왼쪽
	int mIsMotionRL;
	float mSpeed;
	float mGravity;

	bool mIsStopper;
	bool mIsClimb;
	bool mIsBoom;
	bool mIsCrash;
	bool mIsFallDead;
	bool mIsDig;
	bool mIsTrap;

public:
	Player(const string& name,float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void mapRender(HDC map)override;

	float GetX() { return mX; }
	float GetY() { return mY; }
	
	void GetXPosition(int X) { mX += X; }
	
	int GetIntMotionRL()const { return mIsMotionRL; }
	void SetIntMotionRL(int intMotionRL) { mIsMotionRL = intMotionRL; }
	void SetState(int intMotionRL) { mIsMotionRL = intMotionRL; }

	State* GetState()const { return mCurrentState; }
	void SetState(State* state) { mCurrentState = state; }

	float GetSpeed()const { return mSpeed; }
	void SetSpeed(float speed){ mSpeed = speed; }
	
	float GetGravity()const { return mGravity; }
	void SetGravity(float gravity) { mGravity = gravity; }

	PlayerState GetPlayerState() const { return mPlayerState; }
	void SetPlayerState(PlayerState playerState) { mPlayerState = playerState; }

	bool GetIsGoal()const { return mIsGoal; }
	void SetIsGoal(bool isGoal) { mIsGoal = isGoal; }

	bool GetIsDoor()const { return mIsDoor; }
	void SetIsDoor(bool isDoor) { mIsDoor = isDoor; }

	bool GetIsChange()const { return mIsChange; }
	void SetIsChange(bool isChange) { mIsChange = isChange; }

	bool GetIsClimb()const { return mIsClimb; }
	void SetIsClimb(bool isClimb) { mIsClimb = isClimb; }

	bool GetIsStopper()const { return mIsStopper; }
	void SetIsStopper(bool isStopper) { mIsStopper = isStopper; }

	bool GetIsBoom()const { return mIsBoom; }
	void SetIsBoom(bool isBoom) { mIsBoom = isBoom; }

	bool GetIsFallDead()const { return mIsFallDead; }
	void SetIsFallDead(bool isFallDead) { mIsFallDead = isFallDead; }

	bool GetIsDig()const { return mIsDig; }
	void SetIsDig(bool isDig) { mIsDig = isDig; }

	bool GetIsTrap()const { return mIsTrap; }
	void SetIsTrap(bool istrap) { mIsTrap = istrap; }
};

