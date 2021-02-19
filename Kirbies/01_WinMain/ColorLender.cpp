#include "pch.h"
#include "ColorLender.h"

void ColorLender::ColorRectRender(HDC hdc, RECT rc, int r, int g, int b) 
{
	HBRUSH newBrush = CreateSolidBrush(RGB(r, g, b));
	HBRUSH prevBrush = (HBRUSH)SelectObject(hdc, newBrush);
	RenderRect(hdc, rc);
	SelectObject(hdc, prevBrush);
	DeleteObject(newBrush);
}

void ColorLender::ColerEllipseRender(HDC hdc, float x, float y, float radius, int r, int g, int b)
{
	HBRUSH newBrush = CreateSolidBrush(RGB(r, g, b));
	HBRUSH prevBrush = (HBRUSH)SelectObject(hdc, newBrush);
	RenderEllipse(hdc, x, y, radius);
	SelectObject(hdc, prevBrush);
	DeleteObject(newBrush);
}

void ColorLender::ColerLineRender(HDC hdc, float startX, float startY, float endX, float endY, int r, int g, int b)
{
	HBRUSH newBrush = CreateSolidBrush(RGB(r, g, b));
	HBRUSH prevBrush = (HBRUSH)SelectObject(hdc, newBrush);
	RenderLine(hdc, startX, startY, endX, endY);
	SelectObject(hdc, prevBrush);
	DeleteObject(newBrush);
}
