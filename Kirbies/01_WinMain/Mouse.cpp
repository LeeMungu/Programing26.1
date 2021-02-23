#include "pch.h"
#include "Mouse.h"
#include "Image.h"
#include "Camera.h"
#include "Player.h"
#include "Ui.h"
Mouse::Mouse(const string& name)
	:GameObject(name)
{
}

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
		POINT playerPoint = CameraManager::GetInstance()->GetMainCamera()->GetPoint(player[i]->GetX(), player[i]->GetY());
		if (PtInRect(&mRect, playerPoint))
		{
			mIndexX = 1;
			if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
			{
				Player* tempPlayer = (Player*)player[i];
				tempPlayer->SetPlayerState(mPlayerState);
				tempPlayer->SetIsChange(true);

				//if (mPlayerState == PlayerState::BoomState) {
				//	Ui* ui = (Ui*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Mouse, "BoomBtn");
				//	ui->SetStateBtnCount();
				//}
				//else if (mPlayerState == PlayerState::ClimbState) {
				//	Ui* ui = (Ui*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Mouse, "ClimbBtn");
				//	ui->SetStateBtnCount();
				//}
				//else if (mPlayerState == PlayerState::DigState) {
				//	Ui* ui = (Ui*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Mouse, "DigBtn");
				//	ui->SetStateBtnCount();
				//}
				//else if (mPlayerState == PlayerState::UmbrellaState) {
				//	Ui* ui = (Ui*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Mouse, "UmbrellaBtn");
				//	ui->SetStateBtnCount();
				//}
				//else if (mPlayerState == PlayerState::StopperState) {
				//	Ui* ui = (Ui*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Mouse, "StopeerBtn");
				//	ui->SetStateBtnCount();
				//}

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
		HPEN newPen = CreatePen(PS_SOLID, 5, RGB(100, 0, 100));
		HPEN prevPen = (HPEN)SelectObject(hdc, newPen);
		RenderRect(hdc, mRect);
		SelectObject(hdc, prevPen);
		DeleteObject(newPen);
	}

	mImage->FrameRender(hdc, mRect.left, mRect.top, mIndexX, 0);
}
