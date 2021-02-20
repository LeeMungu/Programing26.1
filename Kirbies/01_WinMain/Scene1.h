#pragma once
#include "Scene.h"
class Scene1 : public Scene
{
	bool mIsSpecial;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;

	void SetIsSpecial(bool isSpecial) { mIsSpecial = isSpecial; }
};

