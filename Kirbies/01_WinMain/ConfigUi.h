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
class ConfigUi : public Ui
{
	Image* mImage;
	Image* mMenuImage;
	Image* mSubImage;


	ButtonUi* mMenuEnd;
	ButtonUi* mMenuRestart;
	ButtonUi* mMenuRecord;
	ButtonUi* mMenuSound;

	float msubsizeX;
	bool mIsSoundMenuOpen;

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
};

