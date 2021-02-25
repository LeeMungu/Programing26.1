#pragma once
#include "GameObject.h"
class DataUI : public GameObject
{
	class CountingPlayerUI* mCountingPlayerUI;
	float mTime;
	float mGoal;

public:
	DataUI(string name, float x, float y);
	virtual void Init()override;
	virtual void Release()override;
	virtual void Update()override;
	virtual void Render(HDC hdc)override;
};

