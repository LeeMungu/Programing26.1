#pragma once
#include "GameObject.h"

//���� �� Ŭ������ �ɰְ�
enum class type : int
	{
		UpAndDown = 0,
		Size = 1,
		S = 2,
		RightToLeft = 3,
		LeftToRight = 4,
		End
	};

class Image;
class Title : public GameObject
{
	
	//UpAndDown
	enum class State
	{
		Up,
		Down,
		Stop
	};
	Title::State mState;
	float mUpLimit;

	bool mIsSize;
	
	type mType;
	Image* mImage;
public:
	Title(Title::type type , wstring key);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};

