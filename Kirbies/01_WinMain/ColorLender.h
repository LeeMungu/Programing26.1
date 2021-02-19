#pragma once
class ColorLender
{
	Singleton(ColorLender)
private:
public:
	void ColorRectRender(HDC hdc,RECT rc, int r, int g, int b);
	void ColerEllipseRender(HDC hdc, float x, float y, float radius, int r, int g, int b);
	void ColerLineRender(HDC hdc, float startX, float startY, float endX, float endY, int r, int g, int b);
};

