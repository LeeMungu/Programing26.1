#pragma once
#include "Scene.h"

class Image;
class EndingText;
class SceneEnding : public Scene
{
	//���� �ؿ� ������� �ؽ�Ʈ �־��ִ� ģ��
	EndingText* mEndText;
	//�ؽ�Ʈ �����ӹ�ȣ
	int mIndexY;
public:
	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};

