#pragma once
#include "Camera.h"
#include "SceneManager.h"
#include "Door.h"
//interface class : 순수가상함수만을 가지고 있는 클래스
class IEvent
{
public:
	//자동적으로 순수 가상함수가 된다
	virtual void Start() = 0;	//이벤트 시작할 때 호출되는 함수
	//실행하다가 끝나면 return true
	virtual bool Update() = 0;	//이벤트 업데이트 함수
};

class IChangeCameraTargetEvent : public IEvent
{
	class GameObject* mTarget;
public:
	IChangeCameraTargetEvent(class GameObject* target);

	void Start()override;
	bool Update()override;
};

class IChangeCameraModeEvent : public IEvent
{
	Camera::Mode mMode;
public:
	IChangeCameraModeEvent(Camera::Mode mode);

	void Start()override;
	bool Update()override;
};

class IDelayEvent : public IEvent
{
	float mCurrentTime;
	float mDelayTime;
public:
	IDelayEvent(float delayTime);

	void Start()override;
	bool Update()override;
};

class ITextEvent : public IEvent
{
	class TextBox* mTextBox;
	float mTimeCount;
	float mLimitTime;
public:
	ITextEvent(class TextBox* textBox);

	void Start()override;
	bool Update()override;
};

class IDoorController : public IEvent
{
	class Door* mDoor;
	bool mIsGeneration;
public:
	IDoorController(class Door* door, bool isGeneraion);

	void Start()override;
	bool Update()override;
};

class INpcController : public IEvent
{
	class NPC* mNpc;
	bool mIsGo;
	int mMotionRL;
public:
	//npc, 이동여부, 오른쪽0-왼쪽1
	INpcController(class NPC* npc, bool isGo, int motionRL);

	void Start()override;
	bool Update()override;
};