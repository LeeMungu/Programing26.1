#pragma once
#include "GameObject.h"
#include "Player.h"
class Ui : public GameObject
{
	class Player* mPlayer;
	class Image* mImage;
	class Image* mCountImage;

	PlayerState mState;

	int mCountNum;
	int mFrameX, mFrameY;

	bool mIsClicked;

public:
	Ui(PlayerState state, float x, float y, int count);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetPlayerPtr(Player* player) { mPlayer = player; }

};

