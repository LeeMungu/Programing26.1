#pragma once
/*
���Ǳ� Ui - ESC ������ ���� ���� �ǰ� �޴� â�� �����.
â �ۿ��� ���޴������� ���� ���� <-���޴��� ������Ʈ���� �߰����ֱ�
��ư �� Ŭ���� �����Ǿ�� �ȴ�.
*/
#include "GameObject.h"
class Image;
class ButtonUi;
class ConfigUi : public GameObject
{
	Image* mImage;
	Image* mMenuImage;

	ButtonUi* mMenuEnd;
	ButtonUi* mMenuRestart;
	ButtonUi* mMenuRecord;
	ButtonUi* mMenuSound;
public:
	ConfigUi(const string& name);
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

