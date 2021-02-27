#include "pch.h"
#include "GameEvent.h"

#include "TextBox.h"
//������- ��ȯ���� �־��ش�.
IChangeCameraTargetEvent::IChangeCameraTargetEvent(GameObject * target)
{
	mTarget = target;
}
//ó�� ���۽� ������ ��
void IChangeCameraTargetEvent::Start()
{
	CameraManager::GetInstance()->GetMainCamera()->SetTarget(mTarget);
	CameraManager::GetInstance()->GetMainCamera()->ChangeMode(Camera::Mode::Follow);

}
//���������� �ൿ�Ұ�
bool IChangeCameraTargetEvent::Update()
{
	float x = CameraManager::GetInstance()->GetMainCamera()->GetX();
	float y = CameraManager::GetInstance()->GetMainCamera()->GetY();

	if (Math::GetDistance(x, y, mTarget->GetX(), mTarget->GetY()) <= 5.0f)
	{
		//Ʈ���϶� ����
		return true;
	}
	//false �϶� ��
	return false;
}

IChangeCameraModeEvent::IChangeCameraModeEvent(Camera::Mode mode)
{
	mMode = mode;
}
void IChangeCameraModeEvent::Start()
{
	CameraManager::GetInstance()->GetMainCamera()->ChangeMode(mMode);
}
bool IChangeCameraModeEvent::Update()
{
	if (CameraManager::GetInstance()->GetMainCamera()->GetMode()
		!=mMode)
	{
		return true;
	}

	return false;
}

IDelayEvent::IDelayEvent(float delayTime)
{
	mDelayTime = delayTime;
	mCurrentTime = 0.f;
}

void IDelayEvent::Start()
{
}

bool IDelayEvent::Update()
{
	mCurrentTime += Time::GetInstance()->DeltaTime();

	if (mCurrentTime >= mDelayTime)
	{
		return true;
	}

	return false;
}

ITextEvent::ITextEvent(TextBox* textBox)
{
	mTextBox = textBox;
}

void ITextEvent::Start()
{
	mTextBox->SetIsActive(true);
	mLimitTime = 2.f;
	mTimeCount = 0.f;
}

bool ITextEvent::Update()
{
	

	if (mTextBox->GetIsTextEnd() == true)
	{
		mTimeCount += Time::GetInstance()->DeltaTime();
		return true;
	}
	return false;
}
