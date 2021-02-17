#include "pch.h"
#include "Scene2.h"

void Scene2::Init()
{
}

void Scene2::Release()
{
}

void Scene2::Update()
{
}

void Scene2::Render(HDC hdc)
{
	wstring str = L"³ª Scene2";
	TextOut(hdc,WINSIZEX / 2, WINSIZEY / 2, str.c_str(), str.length());
}
