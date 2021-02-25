#pragma once
#include "Ui.h"
class DataUI : public Ui
{
	class CountingPlayerUI* mCountingPlayerUI;
	float mTime;
	float mGoalPercent;

public:
	DataUI(string name, float x, float y, int stage);
	virtual void Init()override;
	virtual void Release()override;
	virtual void Update()override;
	virtual void Render(HDC hdc)override;


};

