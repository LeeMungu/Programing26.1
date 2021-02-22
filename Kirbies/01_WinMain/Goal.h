#pragma once
#include "GameObject.h"

class Image;
class Goal : public GameObject
{
	Image* mIamge;
	int mFrameX;
	int mFrameY;
private:
	Goal(const string& name, float x, float y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};

