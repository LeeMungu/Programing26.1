#include "pch.h"
#include "Scene.h"
#include "Special.h"
#include "SpecialApearEffect.h"
#include "Camera.h"

void Scene::SpecialFunc()
{
	if (mIsSpecial == false &&
		Input::GetInstance()->GetKeyDown(VK_TAB))
	{
		Camera* prevCamera = (Camera*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Camera, "Camera");
		prevCamera->ChangeMode(Camera::Mode::Follow);

		SpecialApearEffect* effect = new SpecialApearEffect("ApearEffect", 0, -100, L"SpecialAppearEffect", 9, 3);
		effect->Init();
		ObjectManager::GetInstance()->AddObject(ObjectLayer::Effect, effect);
		prevCamera->SetTarget(effect);
		mIsSpecial = true;
	}
	if (mIsSpecial == true &&
		ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Special).size() == NULL &&
		ObjectManager::GetInstance()->GetObjectList(ObjectLayer::Effect).size() == NULL)
	{
		mIsSpecial = false;
		Camera* prevCamera = (Camera*)ObjectManager::GetInstance()->FindObject(ObjectLayer::Camera, "Camera");
		prevCamera->ChangeMode(Camera::Mode::Free);
	}
}