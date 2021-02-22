#pragma once
#include "GameObject.h"
#include "Player.h"

class Image;
class Player; 
class Goal : public GameObject
{
	Player* mPlayer;
	Image* mIamge;
	int mFrameX;
	int mFrameY;
private:
	Goal(const string& name, float x, float y);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

};

