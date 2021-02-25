#pragma once

class BoomRect;
class BoomRectManager
{
	int mX, mY;
public:
	BoomRectManager(float x, float y);
	void Init();
	void Updata();
	void Release();
	void Render(HDC hdc);
};

