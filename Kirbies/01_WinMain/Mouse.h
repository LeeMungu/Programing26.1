#pragma once
#include "GameObject.h"

class Image;
class Mouse : public GameObject
{
	//타게팅 여부 
	enum class Tageting : int
	{
		On=0,
		Off=1,
		End
	};
	Tageting mIsTageting;//bool값도 가능 고민 해보기
	Image* mImage;
public:
	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};

