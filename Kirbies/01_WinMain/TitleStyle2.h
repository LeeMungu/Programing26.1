#pragma once
#include "Title.h"

class TitleStyle2 : public Title
{
public:
	TitleStyle2(wstring key);
	virtual void Init()override;
	virtual void Release()override;
	virtual void Update()override;
};

