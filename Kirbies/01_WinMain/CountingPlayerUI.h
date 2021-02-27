#pragma once
#include "Ui.h"

class CountingPlayerUI : public Ui
{
	class Image* mOutImage;
	class Image* mInImage;
	class Image* mTimeImage;

	float mCountTimer;
	float mTimer;
	int mPlayerCount;
	int mCreatedPlayerCount;
	int mGoalPlayerCount;

	float mGoalPercent;

public:
	CountingPlayerUI(string name, float x, float y, float timer);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	float GetTimer() { return mTimer; }
	float GetGoalPercent() { return mGoalPercent; }
	float GetGoalPlayer() { return mGoalPlayerCount; }

};

