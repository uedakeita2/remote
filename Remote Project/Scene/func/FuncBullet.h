#pragma once
#include "../BaseScene.h"

struct FuncBullet
{
	bool operator()(ActQueT& actQue, void* scene);
private:
	static std::map<UNIT_ID, int> _MaxCount;
};

