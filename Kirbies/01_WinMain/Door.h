#pragma once
#include"GameObject.h"

class Image;
class Door : public GameObject
{
	Image* mImage;
	int mFrameX;
	int mFrameY;
	float mTimer;
	int mCount;
	int mStageCount;
	float mTimeLimit;

	bool mIsCreatedEnd;
	bool mIsGeneration;

public:
	Door(const string& name, float x, float y, int count);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void mapRender(HDC map)override;


	int GetStageCount() { return mStageCount; }
	int GetPlayerCount() { return mCount; }

	bool GetIsCreatedEnd() { return mIsCreatedEnd; }

	bool GetIsGeneration() { return mIsGeneration; }
	void SetGeneration(bool isGeneration) { mIsGeneration = isGeneration; }
};

