#pragma once
/*
컨피그 Ui - ESC 누르면 씬이 정지 되고 메뉴 창을 띄우줌.
창 작용은 씬메니저에서 해줄 예정 <-씬메니저 업데이트에서 추가해주기
버튼 및 클릭도 구현되어야 된다.
*/
#include "GameObject.h"
#include "Ui.h"
class Image;
class ButtonUi;
class SoundBtn;
class Animation;
class ConfigUi : public Ui
{
	Image* mImage;
	Image* mMenuImage;
	Image* mSubImage;
	Image* mSoundImage;
	Image* mEffImage;
	int mIndexX;

	Image* mBgmBar;
	Image* mEffSoundBar;
	float mBgmScaleX;
	float mEffScaleX;

	ButtonUi* mMenuEnd;
	ButtonUi* mMenuRestart;
	ButtonUi* mMenuRecord;
	ButtonUi* mMenuSound;

	SoundBtn* mBgmPlus;
	SoundBtn* mBgmMinus;
	SoundBtn* mEffPlus;
	SoundBtn* mEffMinus;

	float msubsizeX;
	bool mIsSoundMenuOpen;
	bool mIsRecordMenuOpen;

	Animation* mBgmAnimation;
	Animation* mEffAnimaion;

public:
	ConfigUi(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;


	void SetSubMenuOpen(float x) { msubsizeX = x; }
	float GetSubMenu() { return msubsizeX; }

	void SetIsSoundMenu(bool open) { mIsSoundMenuOpen = open; }
	bool GetIsSoundMenu() { return mIsSoundMenuOpen; }

	void SetIsRecordMenu(bool open) { mIsRecordMenuOpen = open; }
	bool GetIsRecordMenu() { return mIsRecordMenuOpen; }

	void SoundIndexX(wstring aniName);


	void SetSoundBarScale(float x) { mBgmScaleX += x; }
	float GetSoundBarScale() { return mBgmScaleX; }
	void SetEffSoundBarScale(float x) { mEffScaleX += x; }
	float GetEffSoundBarScale() { return mEffScaleX; }

};



