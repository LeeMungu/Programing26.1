#include "pch.h"
#include "Scene.h"
#include "Special.h"
#include "SpecialApearEffect.h"
#include "Camera.h"
#include "Ui.h"
#include "GameEvent.h"

Scene::Scene()
{
	mIsGameClear = false;
	mIsGameOver = false;
}

void Scene::Release()
{
	ObjectManager::GetInstance()->Release();
	SoundPlayer::GetInstance()->Stop();
	vector<Ui*> temps = UiManager::GetInstance()->GetUiList(UiLayer::CountPlayerUi);
	if (temps.size() != NULL)
	{
		for (int i = 0; i < temps.size(); i++)
		{
			temps[i]->SetIsActive(false);
		}
	}
}

void Scene::SpecialFunc()
{
	if (mIsSpecial == false &&
		Input::GetInstance()->GetKeyDown('E'))
	{
		Camera* prevCamera = (Camera*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Camera, "Camera");
		prevCamera->ChangeMode(Camera::Mode::Follow);

		SpecialApearEffect* effect = new SpecialApearEffect("ApearEffect", 100, 400, L"SpecialAppearEffect", 9, 3);
		effect->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Effect, effect);
		prevCamera->SetTarget(effect);
		mIsSpecial = true;
	}
	if (mIsSpecial == true &&
		ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Special).size() == NULL &&
		ObjectManager::GetInstance()->GetObjectList(ObjectLayer::SpecialEffect).size() == NULL &&
		ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Effect).size()==NULL)
	{
		mIsSpecial = false;
		CameraManager::GetInstance()->GetMainCamera()->ChangeMode(Camera::Mode::Free);
	}
}

void Scene::CameraWalk()
{
	if (ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Door).size() != NULL)
	{


	}
}

void Scene::FollowPlayer()
{
	if (Input::GetInstance()->GetKeyDown('Q'))
	{
		if (ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player).size() != NULL)
		{

			vector<GameObject*> tempPlayer = ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Player);

			CameraManager::GetInstance()->GetMainCamera()->ChangeMode(Camera::Mode::Follow);
			CameraManager::GetInstance()->GetMainCamera()->SetTarget(tempPlayer[0]);
		}
		else
		{
		}
	}
	if (Input::GetInstance()->GetKeyUp('Q'))
	{
		CameraManager::GetInstance()->GetMainCamera()->ChangeMode(Camera::Mode::Free);
	}
}

