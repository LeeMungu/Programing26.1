#include "pch.h"
#include "Goal.h"

#include "Player.h"
#include "Run.h"

Goal::Goal(const string& name, float x, float y)
	:GameObject(name)
{
	mX = x;
	mY = y;
}

void Goal::Init()
{
    //이미지넣기
	mPlayer->SetIsGoal(false);


	//플레이어에서 불값받아오기
	

}

void Goal::Release()
{
}

void Goal::Update()
{
}

void Goal::Render(HDC hdc)
{
}
