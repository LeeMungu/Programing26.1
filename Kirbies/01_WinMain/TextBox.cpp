#include "pch.h"
#include "TextBox.h"
#include "Image.h"

TextBox::TextBox(const string& name, wstring text, float limitTime)
	:GameObject(name)
{
	mText = text;
	mLimitCountTime = limitTime;
}

void TextBox::Init()
{
	//이미지 찾아넣기
	//mImage
	//mSizeX = mImage->Get
	//mSizeY = mImage->Get
	mX = WINSIZEX / 2;
	mY = WINSIZEY / 4 * 3;
	mRect = RectMakeCenter(mX, mY, mSizeX, mSizeY);
	mCountTime = 0.f;
	mTextLengs = 0;
	mIsTextEnd = false;
}

void TextBox::Update()
{
	mCountTime += Time::GetInstance()->DeltaTime();

	if (mCountTime >= mLimitCountTime)
	{
		mCountTime = 0.f;
		if (mTextLengs < mText.length())
		{
			mTextLengs++;
		}
		else if(mTextLengs >= mText.length() && mIsTextEnd ==false)
		{
			mIsTextEnd = true;
		}
	}
}

void TextBox::Release()
{

}

void TextBox::Render(HDC hdc)
{
	HFONT hFont, oldFont;
	hFont = CreateFont(27, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("Edit Undo BRK"));
	oldFont = (HFONT)SelectObject(hdc, hFont);

	TextOut(hdc, mX, mY, mText.c_str(), mTextLengs);
	
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}
