#include "pch.h"
#include "TextBox.h"
#include "Image.h"

TextBox::TextBox(const string& name, wstring text)
	:GameObject(name)
{
	mText = text;
}

void TextBox::Init()
{
	//�̹��� ã�Ƴֱ�
	//mImage
	
}

void TextBox::Update()
{
}

void TextBox::Release()
{
}

void TextBox::Render(HDC hdc)
{
}
