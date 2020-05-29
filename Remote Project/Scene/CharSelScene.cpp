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
	lpImageMng.GetID("���", "image/player2.png", { 100,100 }, { 5,1 });
	lpImageMng.GetID("ײ�", "image/life.png", { 240,100 }, { 5,1 });
	lpImageMng.GetID("�g2", "image/frame2.png");

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


	lpSceneMng.AddDrawQue({ IMAGE_ID("���")[PlayerNo],200.0,300.0,0,0,LAYER::UI,DX_BLENDMODE_NOBLEND,255 });
	lpSceneMng.AddDrawQue({ IMAGE_ID("���")[EnemyNo],600.0,300.0,0,0,LAYER::UI,DX_BLENDMODE_NOBLEND,255 });
	lpSceneMng.AddDrawQue({ IMAGE_ID("ײ�")[PlayerNo],200.0,450.0,0,0,LAYER::UI,DX_BLENDMODE_NOBLEND,255 });
	lpSceneMng.AddDrawQue({ IMAGE_ID("ײ�")[EnemyNo],600.0,450.0,0,0,LAYER::UI,DX_BLENDMODE_NOBLEND,255 });
	lpSceneMng.AddDrawQue({ IMAGE_ID("�g2")[0],400.0,300.0,0,0,LAYER::BG,DX_BLENDMODE_NOBLEND,255 });



	OldKeyFlag = KeyFlag;
	EOldKeyFlag = EKeyFlag;

	if ((PEnterFlag)&&(EEnterFlag))
	{
		switch (PlayerNo)
		{
		case 0:	// �o�����X
			PlayerLife = 3;
			PMaxBoundCnt = 4;
			PBulletCnt = 3;
			PSpeed = 1.0;
			break;
		case 1:	// �p���[
			PlayerLife = 2;
			PMaxBoundCnt = 4;
			PBulletCnt = 4;
			PSpeed = 1.0;
			break;
		case 2:	// �X�s�[�h
			PlayerLife = 3;
			PMaxBoundCnt = 3;
			PBulletCnt = 3;
			PSpeed = 1.2;
			break;
		case 3:	// �^���N
			PlayerLife = 4;
			PMaxBoundCnt = 4;
			PBulletCnt = 3;
			PSpeed = 0.9;
			break;
		case 4:	// �e�N�j�b�N
			PlayerLife = 3;
			PMaxBoundCnt = 5;
			PBulletCnt = 2;
			PSpeed = 1.0;
			break;
		default:
			"�G���[";
			break;
		}

		switch (EnemyNo)
		{
		case 0:	// �o�����X
			EnemyLife = 3;
			EMaxBoundCnt = 4;
			EBulletCnt = 3;
			ESpeed = 1.0;
			break;
		case 1:	// �p���[
			EnemyLife = 2;
			EMaxBoundCnt = 4;
			EBulletCnt = 4;
			ESpeed = 1.0;
			break;
		case 2:	// �X�s�[�h
			EnemyLife = 3;
			EMaxBoundCnt = 3;
			EBulletCnt = 3;
			ESpeed = 1.2;
			break;
		case 3:	// �^���N
			EnemyLife = 4;
			EMaxBoundCnt = 4;
			EBulletCnt = 3;
			ESpeed = 0.9;
			break;
		case 4:	// �e�N�j�b�N
			EnemyLife = 3;
			EMaxBoundCnt = 5;
			EBulletCnt = 2;
			ESpeed = 1.0;
			break;
		default:
			"�G���[";
			break;
		}

		lpSceneMng.PMaxBoundCnt = PMaxBoundCnt;
		lpSceneMng.EMaxBoundCnt = EMaxBoundCnt;
		lpSceneMng.PBulletCnt = PBulletCnt;
		lpSceneMng.EBulletCnt = EBulletCnt;
		lpSceneMng.PSpeed = PSpeed;
		lpSceneMng.ESpeed = ESpeed;
		lpSceneMng.PLife = PlayerLife;
		lpSceneMng.ELife = EnemyLife;
		lpSceneMng.PlayerNo = PlayerNo;
		lpSceneMng.EnemyNo = EnemyNo;
		return std::make_unique<GameScene>();
	}

	return std::move(own);
}
