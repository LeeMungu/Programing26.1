#include "pch.h"
#include "Mouse.h"
#include "Image.h"


void Mouse::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Mouns");
	mX = _mousePosition.x;
	mY = _mousePosition.y;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Mouse::Release()
{

}

void Mouse::Update()
{
	//�̵�
	mX = _mousePosition.x;
	mY = _mousePosition.y;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
}

void Mouse::Render(HDC hdc)
{
	
	//���콺 ��Ʈ ǥ�� ������ ����
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 0, 0, 255);
	}
}
