#pragma once
#include "Ui.h"
class DataUI : public Ui
{
	class CountingPlayerUI* mCountingPlayerUI;
	float mTime;
	float mGoalPercent;


public:
	DataUI(const string& name, int stage);
	virtual void Init() override;
	virtual void Render(HDC hdc)override;


};

