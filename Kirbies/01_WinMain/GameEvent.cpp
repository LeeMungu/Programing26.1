#include "pch.h"
#include "GameEvent.h"

#include "TextBox.h"
#include "Door.h"
#include "NPC.h"
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

	if (CameraManager::GetInstance()->GetMainCamera()->GetFollowEnd()==true)
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
		==mMode)
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
		if (mTimeCount > mLimitTime)
		{
			mTextBox->SetIsDestroy(true);
			return true;
		}
	}
	return false;
}


IDoorController::IDoorController(class Door* door, bool isGeneration)
{
	mDoor = door;
	mIsGeneration = isGeneration;
}

void IDoorController::Start()
{
	mDoor->SetGeneration(mIsGeneration);
}

bool IDoorController::Update()
{
	if (mDoor->GetIsGeneration() == mIsGeneration)
	{
		return true;
	}
	else if (mDoor->GetIsGeneration() != mIsGeneration)
	{
		mDoor->SetGeneration(mIsGeneration);
	}
	return false;
}

INpcController::INpcController(NPC* npc, bool isGo, int motionRL)
{
	mNpc = npc;
	mIsGo = isGo;
	mMotionRL = motionRL;
}

void INpcController::Start()
{
	mNpc->SetIsGo(mIsGo);
	mNpc->SetIsMotionRL(mMotionRL);
}

bool INpcController::Update()
{
	if(mNpc->GetIsGo()==mIsGo && mNpc->GetIsMotionRL()==mMotionRL)
	{ 
		return true;
	}

	return false;
}
