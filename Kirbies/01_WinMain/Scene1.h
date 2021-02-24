#pragma once
#include "Scene.h"


class Scene1 : public Scene
{
	
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
	void mapRender(HDC map)override;

	void SetIsSpecial(bool isSpecial) { mIsSpecial = isSpecial; }

	
};

