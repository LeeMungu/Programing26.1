#pragma once
#include "GameObject.h"

class Image;
class Animation;
class NPC : public GameObject
{
public:
	enum class NPCState
	{
		LeftIdle,
		RightIdle,
		LeftRun,
		RightRun
	};
private:
	Image* mImage;
	Animation* mCurrentAnimation;
	Animation* mLeftIdleAnimation;
	Animation* mRightIdleAnimation;
	Animation* mLeftRunAnimation;
	Animation* mRightRunAnimation;
	NPCState mNpcState;

	int mIsMotionRL;
	bool mIsGo;
public:
	NPC(const string& name, float x, float y);
	void Init() override;
	void Update() override;
	void Release() override;
	void Render(HDC hdc) override;

	int GetIsMotionRL()const { return mIsMotionRL; }
	void SetIsMotionRL(int isMotionRL) { mIsMotionRL = isMotionRL; }

	bool GetIsGo()const { return mIsGo; }
	void SetIsGo(bool isGo) { mIsGo = isGo; }

	NPCState GetState()const{return mNpcState;};
	void SetState(NPCState state) { mNpcState = state; };
};

