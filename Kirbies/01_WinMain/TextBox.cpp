#include "pch.h"
#include "TextBox.h"
#include "Image.h"

TextBox::TextBox(const string& name, wstring text, float limitTime, TextType type)
	:GameObject(name)
{
	mType = type;
	mText = text;
	mLimitCountTime = limitTime;
}

void TextBox::Init()
{
	//이미지 찾아넣기
	if (mType == TextType::Dedede)
	{
		mImage = IMAGEMANAGER->FindImage(L"TextBoxDeDeDe");
	}
	else if (mType == TextType::Kirby)
	{
		mImage = IMAGEMANAGER->FindImage(L"TextBoxKirby");
	}
	mSizeX = mImage->GetWidth();
	mSizeY = mImage->GetHeight();
	mX = WINSIZEX / 2;
	mY = WINSIZEY - mSizeY/2;
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
	mImage->AlphaRender(hdc, mRect.left, mRect.top, 0.7f);

	HFONT hFont, oldFont;
	hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH || FF_ROMAN, TEXT("메이플스토리 Bold"));
	oldFont = (HFONT)SelectObject(hdc, hFont);

	TextOut(hdc, mX-WINSIZEX/3, mY, mText.c_str(), mTextLengs);
	
	SelectObject(hdc, oldFont);
	DeleteObject(hFont);
}
