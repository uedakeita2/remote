#include <algorithm>
#include <DxLib.h>
//#include <_debug\_DebugConOut.h>
#include "GameScene.h"
#include "../common/imageMng.h"
//#include <Player.h>
//#include <Enemy.h>
#include "SceneMng.h"
//#include <Scene/fanc/FuncBullet.h>
//#include <Scene\fanc\FuncCheckHit.h>
//#include <Scene\fanc\FuncShake.h>

GameScene::GameScene()
{
	//initFunc();

	//TRACE("�ްѼ�݂̐���\n");
	lpImageMng.GetID("���", "image/char.png", { 30,32 }, { 10,10 });
	lpImageMng.GetID("�e", "image/shot.png", { 8,3 }, { 1,2 });
	lpImageMng.GetID("�G����", "image/en_blast.png", { 64,64 }, { 5,1 });
	lpImageMng.GetID("PL����", "image/pl_blast.png", { 64,64 }, { 4,1 });

	_objList.emplace_back(
		new Player({ 250.0 , 390.0 - 16.0 }, { 0,0 })
	);

	//j = 0;

	//for (int y = 0; y < 5; y++)
	//{
	//	for (int x = 0; x < 10; x++)
	//	{
	//		MoveState tmpMoveState;	// move�ŏ��L����n���Ă�۰�قŐݒ肵�Ă��邩����v
	//		tmpMoveState.emplace_back(MOVE_TYPE::WAIT, Vector2Dbl{ 30.0 + j * 30.0 , 0.0 });
	//		tmpMoveState.emplace_back(MOVE_TYPE::SIGMOID, Vector2Dbl{ lpSceneMng.GameScreenSize.x * 8.0 / 10.0 - ((j / 3) % 2 * lpSceneMng.GameScreenSize.x / 10.0 * 6.0), (j / 6) % 3 < 2 ? lpSceneMng.GameScreenSize.y / 5.0 * 4.0 : lpSceneMng.GameScreenSize.y / 5.0 * 3.0 - 20.0 });
	//		tmpMoveState.emplace_back(MOVE_TYPE::SPIRAL, Vector2Dbl{ (j / 3) % 2 == 0 ? 100.0 : -100.0 , j % 18 >= 12 ? 10.0 : -10.0 });
	//		tmpMoveState.emplace_back(MOVE_TYPE::PITIN, Vector2Dbl{ 70.0 + x * 40.0 ,  y * 35.0 + 25.0 });
	//		tmpMoveState.emplace_back(MOVE_TYPE::LR, Vector2Dbl{ 70.0 + x * 40.0  , 50.0 });
	//		tmpMoveState.emplace_back(MOVE_TYPE::EXPAND, Vector2Dbl{ 32.0 * 5.0 + 70.0 , 30.0 * 2.0 });
	//		tmpMoveState.emplace_back(MOVE_TYPE::ATTACK, Vector2Dbl{});
	//		tmpMoveState.emplace_back(MOVE_TYPE::PITIN, Vector2Dbl{ 70.0 + x * 40.0 ,  y * 35.0 + 25.0 });
	//		tmpMoveState.emplace_back(MOVE_TYPE::EXPITIN, Vector2Dbl{ 70.0 + x * 40.0 ,  y * 35.0 + 25.0 });

	//		EnemyState data = { ENEMY_TYPE::A,
	//		{ ((j / 3) % 2) * lpSceneMng.GameScreenSize.x - 15.0 + ((j / 3) % 2) * 30 ,(j / 6) % 3 * lpSceneMng.GameScreenSize.y / 2 + 16.0 - ((j / 6) % 3 * 32.0) },
	//		{ 32.0, 30.0 } ,
	//			tmpMoveState
	//		};
	//		_objList.emplace_back(new Enemy(data));

	//		j++;
	//	}
	//}

	//_shakeCount = 0;
}


GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	auto plObj = std::find_if(
		_objList.begin(),
		_objList.end(),
		[](sharedObj plObj) {return ((*plObj).unitID() == UNIT_ID::PLAYER); });

	//if (!FadeUpdate())
	//{
	//	for (auto data : _objList)
	//	{
	//		(*data).Update(*plObj);
	//	}
	//}

	for (auto data : _objList)
	{
		/*data->Draw();*/
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			(*data).SetAlive(false);
		}

		(*data).Draw();
	}

	/*auto prg = [](sharedObj&obj) {return(*obj).isDead(); };
	prg(*_objList.begin());*/

	auto itr = std::remove_if(
		_objList.begin(),	// �����͈͂̊J�n
		_objList.end(),		// �����͈͂̏I��
		[](sharedObj& obj) {return(*obj).isDead(); } 	// ����ł������O �����͐^�U��K���Ԃ�(�v���f�B�P�[�g)
	);
	// itr ���������v�f�̐擪�A�h���X
	_objList.erase(itr, _objList.end());

	//_objList.erase(std::remove_if(
	//					_objList.begin(),	// �����͈͂̊J�n
	//					_objList.end(),		// �����͈͂̏I��
	//					[](sharedObj& obj) {return(*obj).isDead(); } 	// ����ł������O �����͐^�U��K���Ԃ�(�v���f�B�P�[�g)
	//				),
	//	_objList.end());



	return std::move(own);
}


void GameScene::RunActQue(std::vector<ActQueT> actList)
{
	for (auto actQue : actList)
	{
		switch (actQue.first)
		{
		//case ACT_QUE::SHOT:
		//	FuncBullet()(actQue, this);
		//	break;
		//case ACT_QUE::CHECK_HIT:
		//	FuncCheckHit()(actQue, this);
		//	break;
		//default:
		//	AST();
		//	break;
		}
	}
}

