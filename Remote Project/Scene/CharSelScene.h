#pragma once
#include "BaseScene.h"
class CharSelScene :
	public BaseScene
{
public:
	CharSelScene();
	~CharSelScene();
	unique_Base Update(unique_Base own);
	int PadInput;
	int EPadInput;
	int EnemyNo;
	int PlayerNo;
	bool KeyFlag;
	bool OldKeyFlag;
	bool EKeyFlag;
	bool EOldKeyFlag;
	bool PEnterFlag;
	bool EEnterFlag;
};

