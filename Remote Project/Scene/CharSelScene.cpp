#include "CharSelScene.h"
#include "DxLib.h"
#include "GameScene.h"
#include "SceneMng.h"
#include "SceneMng.h"

CharSelScene::CharSelScene()
{
	EnemyNo = 0;
	PlayerNo = 0;
	KeyFlag = false;
	OldKeyFlag = false;
	EKeyFlag = false;
	EOldKeyFlag = false;
	PEnterFlag = false;
	EEnterFlag = false;
	lpImageMng.GetID("·¬×", "image/player2.png", { 100,100 }, { 5,1 });
}

CharSelScene::~CharSelScene()
{
}

unique_Base CharSelScene::Update(unique_Base own)
{
	KeyFlag = false;
	EKeyFlag = false;

	PadInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	EPadInput = GetJoypadInputState(DX_INPUT_PAD2);

	if (!PEnterFlag)
	{
		if ((PadInput & PAD_INPUT_RIGHT) != 0)
		{
			KeyFlag = true;
			if ((!OldKeyFlag) && (KeyFlag))
			{
				PlayerNo++;
			}
		}
		if ((PadInput & PAD_INPUT_LEFT) != 0)
		{
			KeyFlag = true;
			if ((!OldKeyFlag) && (KeyFlag))
			{
				PlayerNo--;
			}
		}
	}

	if ((PadInput & PAD_INPUT_3) != 0)
	{
		PEnterFlag = true;
	}
	if ((PadInput & PAD_INPUT_2) != 0)
	{
		PEnterFlag = false;
	}

	if (!EEnterFlag)
	{
		if ((EPadInput & PAD_INPUT_RIGHT) != 0)
		{
			EKeyFlag = true;
			if ((!EOldKeyFlag) && (EKeyFlag))
			{
				EnemyNo++;
			}
		}
		if ((EPadInput & PAD_INPUT_LEFT) != 0)
		{
			EKeyFlag = true;
			if ((!EOldKeyFlag) && (EKeyFlag))
			{
				EnemyNo--;
			}
		}
	}

	if ((EPadInput & PAD_INPUT_3) != 0)
	{
		EEnterFlag = true;
	}
	if ((EPadInput & PAD_INPUT_2) != 0)
	{
		EEnterFlag = false;
	}




	if (PlayerNo >= 5)
	{
		PlayerNo = 0;
	}
	if (PlayerNo <= -1)
	{
		PlayerNo = 4;
	}
	if (EnemyNo >= 5)
	{
		EnemyNo = 0;
	}
	if (EnemyNo <= -1)
	{
		EnemyNo = 4;
	}


	lpSceneMng.AddDrawQue({ IMAGE_ID("·¬×")[PlayerNo],200.0,300.0,0,0,LAYER::UI,DX_BLENDMODE_NOBLEND,255 });
	lpSceneMng.AddDrawQue({ IMAGE_ID("·¬×")[EnemyNo],600.0,300.0,0,0,LAYER::UI,DX_BLENDMODE_NOBLEND,255 });

	OldKeyFlag = KeyFlag;
	EOldKeyFlag = EKeyFlag;

	if ((PEnterFlag)&&(EEnterFlag))
	{
		switch (PlayerNo)
		{
		case 0:
			PlayerLife = 3;
			break;
		case 1:
			break;
		}

		lpSceneMng.PlayerNo = PlayerNo;
		lpSceneMng.EnemyNo = EnemyNo;
		return std::make_unique<GameScene>();
	}

	return std::move(own);
}
