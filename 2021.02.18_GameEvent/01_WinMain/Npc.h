#pragma once
#include "GameObject.h"
class Npc : public GameObject
{
	class Image* mImage;
	class Animation* mIdleAnimation;
	class Animation* mRunAnimation;
	class Animation* mCurrentAnimation;	//현재 애니메이션

	bool mIsWin;
	bool mIsPlaced;
public:
	Npc(const string& name, float x, float y);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetWin() { mIsWin = true; }
};

