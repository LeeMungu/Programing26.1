#pragma once

class Image;
class Animation;
class Player;
class State
{
protected:
	Image* mImage;
	Animation* mAnimation;
	Player* mPlayer;
public:
	virtual void Init() {}
	virtual void Release(){}
	virtual void Update(){}
	virtual void Render(HDC hdc){}

	void SetPlayerPtr(Player* player) { mPlayer = player; }
};

