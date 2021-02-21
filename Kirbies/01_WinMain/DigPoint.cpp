#include "pch.h"
#include "DigPoint.h"
#include "Camera.h"

DigPoint::DigPoint(HDC hdc, int x, int y, float radius)
{
	mX = x;
	mY = y;
	mRadius = radius;
	Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
}

void DigPoint::Render(HDC hdc)
{
	CameraManager::GetInstance()->GetMainCamera()->RenderEllipse(hdc, mX, mY, mRadius);
}