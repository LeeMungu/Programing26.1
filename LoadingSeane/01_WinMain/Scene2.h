#pragma once
#include "Scene.h"
//final : 문구 왈 => 불임시키는 것
class Scene2 final : public Scene
{
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};
