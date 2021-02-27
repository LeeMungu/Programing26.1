#pragma once
#include"GameObject.h"
enum class TextType
{
	Kirby,
	Dedede
};
class Image;
class TextBox : public GameObject
{
	
	Image* mImage;
	wstring mText;
	int mTextLengs;
	float mCountTime;
	float mLimitCountTime;
	bool mIsTextEnd;
	TextType mType;
public:
	//오브젝트명, 출력할텍스트, 텍스트 글자 출력 간격, 텍스트 타입
	TextBox(const string& name,wstring text, float limitTime, TextType type);
	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;

	bool GetIsTextEnd()const { return mIsTextEnd; }
	void SetIsTextEnd(bool isTextEnd) { mIsTextEnd = isTextEnd; }
};

