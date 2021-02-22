#pragma once
#include"GameObject.h"

class Image;
class Door : public GameObject
{
	Image* mImage;
	int mFrameX;
	int mFrameY;
	int mTimer;
	int mCount;
public:
	Door(const string& name, float x, float y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

