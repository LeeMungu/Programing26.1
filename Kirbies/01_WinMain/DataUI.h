#pragma once
#include "Ui.h"
class DataUI : public Ui
{
	class Image* mImage;
	class CountingPlayerUI* mCountingPlayerUI;

	vector <Ui*> tempCountingUI;
	vector<float> mTimeList;
	vector<float> mGoalPercentList;

	map<string, float> mTimeMap;
	map<string, float> mGoalMap;
public:
	DataUI(const string& name);
	
	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc)override;

	void SetData();
};

