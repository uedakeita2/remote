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
	int PlayerLife;
	int EnemyLife;
	int PMaxBoundCnt;
	int EMaxBoundCnt;
	int PBulletCnt;
	int EBulletCnt;
	float PSpeed;
	float ESpeed;
	bool KeyFlag;
	bool OldKeyFlag;
	bool EKeyFlag;
	bool EOldKeyFlag;
	bool PEnterFlag;
	bool EEnterFlag;
};

