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
    //�̹����ֱ�
	mPlayer->SetIsGoal(false);


	//�÷��̾�� �Ұ��޾ƿ���
	

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
