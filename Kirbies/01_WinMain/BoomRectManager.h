#pragma once

class BoomRect;
class BoomRectManager
{
	float x, y;
public:
	BoomRectManager(float x, float y);
	void Init();
	void Updata();
	void Release();
	void Render(HDC hdc);
};

