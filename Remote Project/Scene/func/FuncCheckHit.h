#pragma once
#include "../BaseScene.h"


struct FuncCheckHit
{
	bool operator()(ActQueT& actQue, void* scene);
};
