#pragma once
#include"GameObject.h"

class Image;
class TextBox : GameObject
{
	Image mImage;
	wstring mText;
public:
	TextBox(const string& name,wstring text);
	void Init()override;
	void Update()override;
	void Release()override;
	void Render(HDC hdc)override;
};

