#pragma once
#include"GameObject.h"

class Image;
class Door : public GameObject
{
	Image* mImage;
	int mFrameX;
	int mFrameY;
	float mTimer;
	int mCount;
	int mStage1Count;
public:
	Door(const string& name, float x, float y, int count);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

