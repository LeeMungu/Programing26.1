#pragma once
#include "GameObject.h"
#include "Player.h"

class Image;
class Player; 
class Goal : public GameObject
{
	Player* mPlayer;
	Image* mImage;

	int mFrameX;
	int mFrameY;
public:
	Goal(const string& name, float x, float y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void mapRender(HDC map)override;

};

