#pragma once
#include "GameObject.h"


class Image;
class Title : public GameObject
{
protected:
	
	bool mIsSize;
	Image* mImage;
public:
	Title(wstring key);
	virtual void Init()override;
	virtual void Release()override;
	virtual void Update()override;
	virtual void Render(HDC hdc)override;
};
