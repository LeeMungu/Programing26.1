#pragma once
#include "Scene.h"

class Image;
class EndingText;
class SceneEnding : public Scene
{
	//가장 밑에 따라오는 텍스트 넣어주는 친구
	EndingText* mEndText;
	//텍스트 프레임번호
	int mIndexY;
public:
	void Init() override;
	void Release() override;
	void Update() override;
	void Render(HDC hdc) override;
};

