#include "pch.h"
#include "Camera.h"

#include "Image.h"

void Camera::Init()
{
	mMode = Mode::Free;
	mTarget = nullptr;
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 2;
	mSizeX = WINSIZEX;
	mSizeY = WINSIZEY;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mMoveSpeed = 5.f;
	mFollowEnd = false;
}

void Camera::Release()
{
	//얘도 쓸일이 없다 . . . 
}

void Camera::Update()
{
	RECT bottomRC = ObjectManager::GetInstance()->FindObject(ObjectLayer::Bottom, "Bottom")->GetRect();
	mFollowEnd = false;
	switch (mMode)
	{
	case Camera::Mode::Follow:
		if (mTarget)
		{
			//mX = mTarget->GetX();
			//mY = mTarget->GetY();
			//멀리있으면 빨리 쫓아가야하고 가까이 있으면 천천히 쫓아가야함
			mX = Math::Lerp(mX, mTarget->GetX(), 2.f * Time::GetInstance()->DeltaTime());
			mY = Math::Lerp(mY, mTarget->GetY(), 2.f * Time::GetInstance()->DeltaTime());
			//카메라 보정
			if (mX < bottomRC.left + WINSIZEX)
			{
				mX = bottomRC.left + WINSIZEX;
				mFollowEnd = true;
			}
			if (mX > bottomRC.right)
			{
				mX = bottomRC.right;
				mFollowEnd = true;
			}
			if (mY < bottomRC.top + WINSIZEY)
			{
				mY = bottomRC.top + WINSIZEY;
				mFollowEnd = true;
			}
			if (mY > bottomRC.bottom)
			{
				mY = bottomRC.bottom;
				mFollowEnd = true;
			}
			if (Math::GetDistance(mX, mY, mTarget->GetX(), mTarget->GetY()) <= 5.0f)
			{
				mFollowEnd = true;
			}


			mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		}
		break;
	case Camera::Mode::Free:
		//키보드 카메라 이동
		//if (Input::GetInstance()->GetKey('A'))mX -= mMoveSpeed;
		//if (Input::GetInstance()->GetKey('D'))mX += mMoveSpeed;
		//if (Input::GetInstance()->GetKey('W'))mY -= mMoveSpeed;
		//if (Input::GetInstance()->GetKey('S'))mY += mMoveSpeed;

		//마우스 위치에 따른 이동
		if (_mousePosition.x <= 0 + 30)
		{
			mX -= mMoveSpeed;
		}
		if (_mousePosition.x >= WINSIZEX - 30)
		{
			mX += mMoveSpeed;
		}
		if (_mousePosition.y <= 0 + 30)
		{
			mY -= mMoveSpeed;
		}
		if (_mousePosition.y >= WINSIZEY - 30)
		{
			mY += mMoveSpeed;
		}
		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

		//클릭으로 이동 (사장된 프로젝트입니다.----)
		//if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
		//{
		//	mouseX = _mousePosition.x;
		//	mouseY = _mousePosition.y;
		//}
		//if (Input::GetInstance()->GetKey(VK_LBUTTON))
		//{
		//	mX += (mouseX - _mousePosition.x);
		//	mY += (mouseY - _mousePosition.y);
		//	mouseX = _mousePosition.x;
		//	mouseY = _mousePosition.y;
		//}

		//카메라 보정
		if (mX < bottomRC.left + WINSIZEX)
			mX = bottomRC.left + WINSIZEX;
		
		if (mX > bottomRC.right )
			mX = bottomRC.right;
		
		if (mY < bottomRC.top + WINSIZEY) 
			mY = bottomRC.top + WINSIZEY;
		
		if (mY > bottomRC.bottom ) 
			mY = bottomRC.bottom;

		mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
		break;
	}


	
}

void Camera::Render(HDC hdc)
{
	//쓸일이 없다 . . . . 
}

void Camera::Render(HDC hdc, Image * image, int x, int y)
{
	image->Render(hdc, x - mRect.left, y - mRect.top);
}

void Camera::Render(HDC hdc, Image * image, int x, int y, int tempX, int tempY, int tempWidth, int tempHeight)
{
	image->Render(hdc, x - mRect.left, y - mRect.top, tempX, tempY, tempWidth, tempHeight);
}

void Camera::FrameRender(HDC hdc, Image * image, int x, int y, int frameX, int frameY)
{
	image->FrameRender(hdc, x - mRect.left, y - mRect.top, frameX, frameY);
}

void Camera::AlphaRender(HDC hdc, Image * image, int x, int y, float alpha)
{
	image->AlphaRender(hdc, x - mRect.left, y - mRect.top, alpha);
}

void Camera::AlphaFrameRender(HDC hdc, Image * image, int x, int y, int frameX, int frameY, float alpha)
{
	image->AlphaFrameRender(hdc, x - mRect.left, y - mRect.top, frameX, frameY, alpha);
}

void Camera::ScaleRender(HDC hdc, Image * image, int x, int y, int width, int height)
{
	image->ScaleRender(hdc, x - mRect.left, y - mRect.top, width, height);
}

void Camera::ScaleFrameRender(HDC hdc, Image * image, int x, int y, int frameX, int frameY, int width, int height)
{
	image->ScaleFrameRender(hdc, x - mRect.left, y - mRect.top, frameX, frameY, width, height);
}

void Camera::AlphaScaleRender(HDC hdc, Image * image, int x, int y, int width, int height, float alpha)
{
	image->AlphaScaleRender(hdc, x - mRect.left, y - mRect.top, width, height, alpha);
}

void Camera::AlphaScaleFrameRender(HDC hdc, Image * image, int x, int y, int frameX, int frameY, int width, int height, float alpha)
{
	image->AlphaScaleFrameRender(hdc, x - mRect.left, y - mRect.top, frameX, frameY, width, height, alpha);
}

/*
::
*/
void Camera::RenderRect(HDC hdc, RECT rc)
{
	rc.left -= mRect.left;
	rc.right -= mRect.left;
	rc.top -= mRect.top;
	rc.bottom -= mRect.top;
	::RenderRect(hdc, rc);
}

void Camera::RenderEllipse(HDC hdc, float x, float y, float radius)
{
	RenderEllipse(hdc, x - mRect.left, y - mRect.top, radius);
}

void Camera::RenderLine(HDC hdc, float startX, float startY, float endX, float endY)
{
	RenderLine(hdc, startX- mRect.left, startY - mRect.top, endX - mRect.left, endY - mRect.top);
}

bool Camera::IsInCameraArea(float x, float y, float width, float height)
{
	RECT rc = RectMakeCenter(x, y, width, height);
	return IsInCameraArea(rc);
}

bool Camera::IsInCameraArea(RECT rc)
{
	if (rc.right < mRect.left)return false;
	if (rc.left > mRect.right)return false;
	if (rc.bottom < mRect.top)return false;
	if (rc.top > mRect.bottom)return false;

	return true;
}
