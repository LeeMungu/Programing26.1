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
	//������Ʈ��, ������ؽ�Ʈ, �ؽ�Ʈ ���� ��� ����, �ؽ�Ʈ Ÿ��
	TextBox(const string& name,wstring text, float limitTime, TextType type);
	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;

	bool GetIsTextEnd()const { return mIsTextEnd; }
	void SetIsTextEnd(bool isTextEnd) { mIsTextEnd = isTextEnd; }
};

