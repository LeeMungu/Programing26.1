#pragma once
#include "GameObject.h"
#include "Player.h"
class Ui : public GameObject
{
	class Player* mPlayer;
	class Image* mImage;
	class Image* mCountUI; //숫자 넣는 곳 ui
	class Image* mCountTens; //10의자리
	class Image* mCountUnits; //1의자리

	class Mouse* mMouse;

	PlayerState mState;
	PlayerState mGetState;

	int mCountNum;
	int mTensNum; //10의 자리 저장
	int mUnitsNum; //1의 자리 저장
	int mFrameX, mFrameY;

public:
	Ui(const string& name, PlayerState state, float x, float y, int count);
	Ui(const string& name);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	int GetStateBtnCount() { return mCountNum; }
	void SetStateBtnCount() { if(mCountNum>0)mCountNum -= 1;}

	//void SetPlayerPtr(Player* player) { mPlayer = player; }
};

