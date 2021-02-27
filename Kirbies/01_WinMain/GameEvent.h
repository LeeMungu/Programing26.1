#pragma once
#include "Camera.h"
//interface class : ���������Լ����� ������ �ִ� Ŭ����
class IEvent
{
public:
	//�ڵ������� ���� �����Լ��� �ȴ�
	virtual void Start() = 0;	//�̺�Ʈ ������ �� ȣ��Ǵ� �Լ�
	//�����ϴٰ� ������ return true
	virtual bool Update() = 0;	//�̺�Ʈ ������Ʈ �Լ�
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