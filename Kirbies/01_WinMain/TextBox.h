#pragma once
#include"GameObject.h"

class Image;
class TextBox : public GameObject
{
	Image* mImage;
	wstring mText;
	int mTextLengs;
	float mCountTime;
	float mLimitCountTime;
	bool mIsTextEnd;
public:
	//������Ʈ��, ������ؽ�Ʈ, �ؽ�Ʈ ���� ��� ����
	TextBox(const string& name,wstring text, float limitTime);
	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;

	bool GetIsTextEnd()const { return mIsTextEnd; }
	void SetIsTextEnd(bool isTextEnd) { mIsTextEnd = isTextEnd; }
};

