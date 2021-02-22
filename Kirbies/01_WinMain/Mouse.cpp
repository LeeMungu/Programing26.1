#include "pch.h"
#include "Mouse.h"
#include "Image.h"
#include "Camera.h"

void Mouse::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Mouns");
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
	
	//if(int i; i<player->GetRect)

	

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
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 0, 0, 255);
	}

	CameraManager::GetInstance()->GetMainCamera()
		->FrameRender(hdc, mImage, mX, mY, mIndexX, 0);
}
