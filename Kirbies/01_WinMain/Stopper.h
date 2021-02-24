#pragma once
#include "State.h"

class State;
class Image;
class Animation;
class Stopper : public State
{

	Animation* mStopperAnimation;
	Animation* mCurrentAnimation;

	class Bottom* mBottom;

	float mX, mY;
	bool mIsPlay;	//플레이중이냐
	bool mIsLoop;	//루프냐


	int mCurrentFrameIndex;	//현재 프레임 인덱스 
	float mCurrentFrameTime;	//현재 프레임 감는 시간
	float mFrameUpdateTime;		//프레임 갱신(증가) 해야하는 시간

	bool mIsObject;

	vector<pair<int, int>> mFrameList;		//프레임 정보
	function<void(void)> mCallbackFunc;		//애니메이션이 전부 플레이되고 끝날 때 실행할 함수

public:
	Stopper();
	void Init();
	void Release();
	void Update();
	void Play();
	void Stop();
	void Render(HDC hdc);
	void mapRender(HDC map)override;

};

