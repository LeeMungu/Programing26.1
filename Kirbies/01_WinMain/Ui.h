#pragma once
#include "GameObject.h"

class Ui : public GameObject
{
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render(HDC hdc)override;
};

