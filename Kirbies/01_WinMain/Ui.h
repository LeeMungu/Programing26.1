#pragma once
#include "GameObject.h"
#include "Player.h"
class Ui : public GameObject
{
	class Player* mPlayer;
	class Image* mImage;
	class Image* mCountUI; //���� �ִ� �� ui
	class Image* mCountTens; //10���ڸ�
	class Image* mCountUnits; //1���ڸ�

	class Mouse* mMouse;

	PlayerState mState;

	int mCountNum;
	int mTensNum; //10�� �ڸ� ����
	int mUnitsNum; //1�� �ڸ� ����
	int mFrameX, mFrameY;

	bool mIsClicked;

public:
	Ui(PlayerState state, float x, float y, int count);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	int GetStateBtnCount() { return mCountNum; }
	void SetStateBtnCount() { mCountNum -= 1;}

	//void SetPlayerPtr(Player* player) { mPlayer = player; }
};

