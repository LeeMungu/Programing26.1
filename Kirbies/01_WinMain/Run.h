#pragma once
#include "State.h"
#include "GameObject.h"
class State;
class Run : public State
{
	enum class RunState : int
	{
		RightMove = 0,
		LeftMove = 1,
		End
	};
	
	RunState mRunState;



};

