#include "pch.h"
#include "LoadingScene1to2.h"
#include "Image.h"

#define PlayerSize 2

void LoadingScene1to2::AddLoadFunc(const function<void(void)>& func)
{
	mLoadList.push_back(func);
}

void LoadingScene1to2::Init()
{
	mLoadIndex = 0;
	mIsEndLoading = false;
}

void LoadingScene1to2::Release()
{
	//이미지 (오브젝트)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Goal", Resources(L"Goal.bmp"), 64 * PlayerSize, 48 * PlayerSize, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Door", Resources(L"Door.bmp"), 47 * PlayerSize, 40 * PlayerSize, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Background", Resources(L"backGround3.bmp"), 768, 336, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Bottom", Resources(L"scene2.bmp"), 2560, 1440, true); });
	

	//이미지 (UI)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"OutUI", Resources(L"out_ui.bmp"), 120, 48, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"InUI", Resources(L"in_ui.bmp"), 120, 48, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"TimeUI", Resources(L"time_ui.bmp"), 144, 48, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Speech", Resources(L"speech.bmp"), 172, 57, 2, 1, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Mouse", Resources(L"cursor_image.bmp"), 110, 55, 2, 1, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Button", Resources(L"Kirby_UI_BUTTON_Package.bmp"), 500, 200, 5, 2, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"UICount", Resources(L"count_ui_image.bmp"), 40, 40, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Numbers", Resources(L"NumberDot.bmp"), 100, 14, 10, 1, true); });

	//이미지 (커비)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Stopper", Resources(L"stopper.bmp"), 110 * PlayerSize, 24 * PlayerSize, 5, 1, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Fall", Resources(L"Fall.bmp"), 400 * PlayerSize, 40 * PlayerSize, 16, 2, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Run", Resources(L"walk.bmp"), 210 * PlayerSize, 38 * PlayerSize, 10, 2, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"GoalKirby", Resources(L"Goalin.bmp"), 138 * PlayerSize, 23 * PlayerSize, 6, 1, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Umbrella", Resources(L"umbrella.bmp"), 900 * PlayerSize, 86 * PlayerSize, 25, 2, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Dig", Resources(L"dig.bmp"), 574 * PlayerSize, 82 * PlayerSize, 14, 2, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Climb", Resources(L"climb.bmp"), 240 * PlayerSize, 52 * PlayerSize, 8, 2, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"Boom", Resources(L"boom.bmp"), 280 * PlayerSize, 32 * PlayerSize, 8, 1, true); });

	//이미지 (왜 필요한지 모르는 여자애)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SpecialAppear", Resources(L"/sp/appear.bmp"), 1328, 540, 8, 3, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SpecialAppearEffect", Resources(L"/sp/appeareffect.bmp"), 2988, 1536, 9, 3, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SpecialAttack", Resources(L"/sp/attack.bmp"), 1494, 720, 9, 4, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SpecialAttackEffect1", Resources(L"/sp/attackeffect1.bmp"), 2560, 512, 10, 2, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SpecialAttackEffect2", Resources(L"/sp/attackeffect2.bmp"), 1600, 1600, 5, 5, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SpecialAttackEffect3", Resources(L"/sp/attackeffect3.bmp"), 2560, 249, 10, 1, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"SpecialEnd", Resources(L"/sp/end.bmp"), 1660, 900, 10, 5, true); });


	//이미지 (이펙트)
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"BoomEffect", Resources(L"boom_Effect.bmp"), 576, 96, 9, 1, true); });
	AddLoadFunc([]() {IMAGEMANAGER->LoadFromFile(L"CountEffect", Resources(L"countNumUI.bmp"), 140, 32, 5, 1, true); });




}

void LoadingScene1to2::Update()
{
}

void LoadingScene1to2::Render(HDC hdc)
{
}
