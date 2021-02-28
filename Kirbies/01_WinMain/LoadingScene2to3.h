#pragma once
#include "Scene.h"
#include <functional>

class LoadingScene2to3 :public Scene3
{
	Image* mLoadingImage;
	Image* mLoadingImage2;
	Image* mLoadingBarImage1;
	Image* mLoadingBarImage2;

	vector<function<void(void)>> mLoadList;
	int mLoadIndex;
	bool mIsEndLoading;

public:
	void AddLoadFunc(const function<void(void)>& func);

	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	bool GetIsEndLoading()const { return mIsEndLoading; }
};

