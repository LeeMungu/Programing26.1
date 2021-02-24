#pragma once
#include "GameObject.h"

class CountingPlayerUI : public GameObject 
{
	class Image* mOutImage;
	class Image* mInImage;
	class Image* mTimeImage;

	class Door* mDoor;
	float mCountTimer;
	float mTimer;
	int mPlayerCount;
	int mCreatedPlayerCount;
	int mGoalPlayerCount;

public:
	CountingPlayerUI(float x, float y, float timer);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

