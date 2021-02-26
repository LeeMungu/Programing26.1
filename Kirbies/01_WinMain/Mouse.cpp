#include "pch.h"
#include "Mouse.h"
#include "Image.h"
#include "Camera.h"
#include "Player.h"
#include "Ui.h"
#include "CountNumEffect.h"
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
	//플레이어 충돌시  mIndexX=1로 해주기
	//카메라에서 플레이어 판정렉트 만들어주기<-실제 렉트가 카메라를 안따라온다.
	vector<GameObject*> player = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player);
	
	mIndexX = 0;
	for (int i=0; i < player.size(); i++)
	{
		//플레이어 판정랙트 따로 만들어주기
		RECT temp;
		POINT playerPoint = CameraManager::GetInstance()->GetMainCamera()->GetPoint(player[i]->GetX(), player[i]->GetY());
		if (PtInRect(&mRect, playerPoint))
		{
			mIndexX = 1;
			Ui* ClimbUI = ClimbUI = (Ui*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "ClimbBtn");
			Ui* StopperUI = (Ui*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "StopperBtn");
			Ui* UmbrellaUI = (Ui*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "UmbrellaBtn");
			Ui* BoomUI = (Ui*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "BoomBtn");
			Ui* DigUI = (Ui*)ObjectManager::GetInstance()->FindObject(ObjectLayer::UI, "DigBtn");


			if (Input::GetInstance()->GetKeyDown(VK_LBUTTON))
			{
				Player* tempPlayer = (Player*)player[i];
				//등산 조건만 다르게 준다. + 스토퍼도
				if (tempPlayer->GetIsClimb()!=true
					&& mPlayerState == PlayerState::ClimbState && ClimbUI->GetStateBtnCount() > 0 )
				{
					tempPlayer->SetIsClimb(true);;
					ClimbUI->SetStateBtnCount();
				}
				else if (tempPlayer->GetIsStopper()!=true 
					&& mPlayerState == PlayerState::StopperState && StopperUI->GetStateBtnCount() > 0)
				{
					if(tempPlayer->GetPlayerState()!=PlayerState::UmbrellaState
						&& tempPlayer->GetPlayerState() != PlayerState::FallState)
					tempPlayer->SetIsStopper(true);
					StopperUI->SetStateBtnCount();
				}
				else if (mPlayerState == PlayerState::UmbrellaState && UmbrellaUI->GetStateBtnCount() > 0)
				{
					if (tempPlayer->GetPlayerState() == PlayerState::FallState)
					{
						tempPlayer->SetPlayerState(mPlayerState);
						tempPlayer->SetIsChange(true);
						UmbrellaUI->SetStateBtnCount();
					}
				}
				else if (tempPlayer->GetIsBoom() != true
					&& mPlayerState == PlayerState::BoomState && BoomUI->GetStateBtnCount() > 0)
				{
		
					CountNumEffect* countEffect = new CountNumEffect("CountEffect", player[i]->GetX(), player[i]->GetRect().top - 10, L"CountEffect");
					countEffect->SetPlayerptr(tempPlayer);
					countEffect->Init();
					tempPlayer->SetIsBoom(true);
					ObjectManager::GetInstance()->AddObject(ObjectLayer::Effect, countEffect);
					BoomUI->SetStateBtnCount();
				}
				else if (tempPlayer->GetIsDig() != true
					&& mPlayerState == PlayerState::DigState && DigUI->GetStateBtnCount() > 0)
				{
					if (tempPlayer->GetPlayerState() != PlayerState::StopperState)
					{
						tempPlayer->SetPlayerState(mPlayerState);
						tempPlayer->SetIsChange(true);
						tempPlayer->SetIsDig(true);
						DigUI->SetStateBtnCount();
					}
				}
				else if (mPlayerState == PlayerState::Empty)
				{
				}
				else if (
					tempPlayer->GetPlayerState() != mPlayerState
					&&
					mPlayerState != PlayerState::ClimbState 
					&& mPlayerState != PlayerState::StopperState
					&& mPlayerState != PlayerState::UmbrellaState
					&& mPlayerState != PlayerState::BoomState
					&& mPlayerState != PlayerState::DigState
					&& mPlayerState != PlayerState::Empty)
				{
					tempPlayer->SetPlayerState(mPlayerState);
					tempPlayer->SetIsChange(true);
				}



				if (mPlayerState == PlayerState::BoomState) {

				}
				else if (mPlayerState == PlayerState::ClimbState) {

				}
				else if (mPlayerState == PlayerState::DigState) {

				}
				else if (mPlayerState == PlayerState::UmbrellaState) {

				}
				else if (mPlayerState == PlayerState::StopperState) {

				}

			}
		}
		//
	}

	//이동
	mX = _mousePosition.x;
	mY = _mousePosition.y;

	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);

}

void Mouse::Render(HDC hdc)
{
	//마우스 랙트 표시 지우지 말것
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
