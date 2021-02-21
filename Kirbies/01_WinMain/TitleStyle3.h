#pragma once
#include "Title.h"

class TitleStyle3 : public Title
{
public:
	TitleStyle3(wstring key);
	virtual void Init()override;
	virtual void Release()override;
	virtual void Update()override;
};