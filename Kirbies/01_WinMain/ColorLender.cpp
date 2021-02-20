#include "pch.h"
#include "ColorLender.h"
#include "Camera.h"

void ColorLender::ColorRectRender(HDC hdc, RECT rc, int r, int g, int b) 
{
	//HBRUSH newBrush = CreateSolidBrush(RGB(r, g, b));
	//HBRUSH prevBrush = (HBRUSH)SelectObject(hdc, newBrush);
	HPEN newPen = CreatePen(PS_SOLID, 8, RGB(r, g, b));
	HPEN prevPen = (HPEN)SelectObject(hdc, newPen);
	CameraManager::GetInstance()->GetMainCamera()->RenderRect(hdc, rc);
	SelectObject(hdc, prevPen);
	DeleteObject(newPen);
	//SelectObject(hdc, prevBrush);
	//DeleteObject(newBrush);
}

void ColorLender::ColerEllipseRender(HDC hdc, float x, float y, float radius, int r, int g, int b)
{
	HPEN newPen = CreatePen(PS_SOLID, 8, RGB(r, g, b));
	HPEN prevPen = (HPEN)SelectObject(hdc, newPen);
	CameraManager::GetInstance()->GetMainCamera()->RenderEllipse(hdc, x, y, radius);
	SelectObject(hdc, prevPen);
	DeleteObject(newPen);
}

void ColorLender::ColerLineRender(HDC hdc, float startX, float startY, float endX, float endY, int r, int g, int b)
{
	HPEN newPen = CreatePen(PS_SOLID, 8, RGB(r, g, b));
	HPEN prevPen = (HPEN)SelectObject(hdc, newPen);
	CameraManager::GetInstance()->GetMainCamera()->RenderLine(hdc, startX, startY, endX, endY);
	SelectObject(hdc, prevPen);
	DeleteObject(newPen);
}
