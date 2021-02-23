#include "pch.h"
#include "Title.h"
#include "Image.h"



Title::Title(wstring key)
{
	mImage = IMAGEMANAGER->FindImage(key);
}

void Title::Init()
{
}

void Title::Release()
{
}

void Title::Update()
{
}

void Title::Render(HDC hdc)
{
	mImage->Render(hdc, mRect.left, mRect.top);
}
