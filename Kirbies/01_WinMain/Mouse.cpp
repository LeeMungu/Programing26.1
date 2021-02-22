#include "pch.h"
#include "Mouse.h"
#include "Image.h"
#include "Camera.h"
#include "Player.h"

void Mouse::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Mouse");
	mX = _mousePosition.x;
	mY = _mousePosition.y;
	mSizeX = mImage->GetFrameWidth();
	mSizeY = mImage->GetFrameHeight();

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

	mIndexX = 0;

	mPlayerState = PlayerState::RunState;
}

void Mouse::Release()
{

}

void Mouse::Update()
{
	//�÷��̾� �浹��  mIndexX=1�� ���ֱ�
	//ī�޶󿡼� �÷��̾� ������Ʈ ������ֱ�<-���� ��Ʈ�� ī�޶� �ȵ���´�.
	vector<GameObject*> player = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player);
	
	mIndexX = 0;
	for (int i=0; i < player.size(); i++)
	{
		//�÷��̾� ������Ʈ ���� ������ֱ�
		RECT temp;
		RECT playerRect = player[i]->GetRect();
		if (PtInRect(&playerRect, _mousePosition))
		{
			mIndexX = 1;
			if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
			{
				Player* tempPlayer = (Player*)player[i];
				tempPlayer->SetPlayerState(mPlayerState);
			}
		}
		//
	}

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

	mImage->FrameRender(hdc, mRect.left, mRect.top, mIndexX, 0);
}
