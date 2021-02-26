#pragma once
#include "Ui.h"
class DataUI : public Ui
{
	class CountingPlayerUI* mCountingPlayerUI;
	float mScore;
	float mTime;
	float mGoalPercent;


public:
	DataUI(const string& name, int stage);
	virtual void Init() override;
	virtual void Render(HDC hdc)override;
	float GetTime() { return mTime; }
	float GetGoalPercent() { return mGoalPercent; }


};

