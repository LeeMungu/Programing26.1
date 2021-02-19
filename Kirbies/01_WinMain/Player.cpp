#include "pch.h"
#include "Player.h"
#include "Image.h"
#include "Animation.h"
#include "Camera.h"
#include "GameObject.h"
#include "State.h"

Player::Player(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Player::Init()
{
	mImage = IMAGEMANAGER->FindImage(L"Player");
	mIntMotionRL = 0;
}

void Player::Release()
{

}

void Player::Update()
{

}

void Player::Render(HDC hdc)
{
	
	//플레이어 판정렉트 보여주는것 손대지 말것! control누르면 나옴
	if (Input::GetInstance()->GetKey(VK_LCONTROL))
	{
		ColorLender::GetInstance()->ColorRectRender(hdc, mRect, 255, 0, 0);
	}
}
