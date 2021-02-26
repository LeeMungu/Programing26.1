#pragma once
/*
���Ǳ� Ui - ESC ������ ���� ���� �ǰ� �޴� â�� �����.
â �ۿ��� ���޴������� ���� ���� <-���޴��� ������Ʈ���� �߰����ֱ�
��ư �� Ŭ���� �����Ǿ�� �ȴ�.
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

	void SoundIndexX(wstring aniName);
};



