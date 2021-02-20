#include "pch.h"
#include "Animation.h"

Animation::Animation()
	:mIsPlay(false), mIsLoop(false), mCurrentFrameIndex(0),
	mCurrentFrameTime(0.f), mFrameUpdateTime(0.f), mCallbackFunc(nullptr) {}

void Animation::Update()
{
	if (mIsPlay == false)
		return;

	float deltaTime = Time::GetInstance()->DeltaTime();

	mCurrentFrameTime += deltaTime;

	if (mCurrentFrameTime >= mFrameUpdateTime)
	{
		//손실 다 없애준다
		while (mCurrentFrameTime >= mFrameUpdateTime)
		{
			mCurrentFrameTime -= mFrameUpdateTime;
		}

		mCurrentFrameIndex++;
		//프레임이 마지막 프레임보다 커지려고 한다면
		if (mCurrentFrameIndex >= mFrameList.size())
		{
			if (mIsLoop == false)
			{
				mIsPlay = false;
				--mCurrentFrameIndex;
			}
			else
			{
				mCurrentFrameIndex = 0;
			}
			//콜백함수가 바인딩 되어 있다면 그 함수 실행
			if (mCallbackFunc != nullptr)
			{
				mCallbackFunc();
			}
		}
	}
}

//플레이
void Animation::Play()
{	
	mIsPlay = true;
}

//리셋
void Animation::Stop()
{
	mIsPlay = false;
	mCurrentFrameIndex = 0;
	mCurrentFrameTime = 0.f;
}

//일시 정지
void Animation::Pause()
{
	mIsPlay = false;
}

void Animation::InitFrameByVector(const vector<pair<int, int>>& frameList)
{
	mFrameList.clear();
	mFrameList = frameList;
}

void Animation::InitFrameByStartEnd(int startX, int startY, int endX, int endY, bool isReverse)
{
	if (isReverse == false)
	{
		for (int y = startY; y <= endY; ++y)
		{
			for (int x = startX; x <= endX; ++x)
			{
				mFrameList.push_back(make_pair(x, y));
			}
		}
	}
	//리버스 트루면 재생끝나고 역순으로
	if (isReverse)
	{
		for (int y = endY; y >= startY; --y)
		{
			for (int x = endX; x >= startX; --x)
			{
				mFrameList.push_back(make_pair(x, y));
			}
		}
	}
}

//뒤에서부터 시작
void Animation::InitFrameByEndStart(int startX, int startY, int endX, int endY, bool isReverse)
{
	if (isReverse == false)
	{
		for (int y = startY; y >= endY; --y)
		{
			for (int x = startX; x >= endX; --x)
			{
				mFrameList.push_back(make_pair(x, y));
			}
		}
	}
	//리버스 트루면 재생끝나고 역순으로
	if (isReverse)
	{
		for (int y = endY; y <= startY; ++y)
		{
			for (int x = endX; x <= startX; ++x)
			{
				mFrameList.push_back(make_pair(x, y));
			}
		}
	}
}

void Animation::SetCallbackFunc(const function<void(void)>& func)
{
	mCallbackFunc = func;
}
