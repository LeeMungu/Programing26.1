#pragma once
/*
컨피그 Ui - ESC 누르면 씬이 정지 되고 메뉴 창을 띄우줌.
창 작용은 씬메니저에서 해줄 예정 <-씬메니저 업데이트에서 추가해주기
버튼 및 클릭도 구현되어야 된다.
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

