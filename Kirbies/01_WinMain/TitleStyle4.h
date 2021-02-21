#pragma once
#include "Title.h"

class TitleStyle4 : public Title
{
public:
	TitleStyle4(wstring key);
	virtual void Init()override;
	virtual void Release()override;
	virtual void Update()override;
};

