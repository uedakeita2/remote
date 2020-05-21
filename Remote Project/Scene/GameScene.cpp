#include <algorithm>
#include <DxLib.h>
#include "../_debug/_DebugConOut.h"
#include "GameScene.h"
#include "../common/imageMng.h"
#include "../Player.h"
#include "../Scene/SceneMng.h"
#include "../Aim.h"
#include "func/FuncBullet.h"
#include "func/FuncCheckHit.h"
#include "../Enemy.h"
#include "../EAim.h"

GameScene::GameScene()
{

	lpImageMng.GetID("���", "image/player.png", { 100,100 }, { 2,1 });
	lpImageMng.GetID("�Ə�", "image/aim.png", { 50,50 }, { 1,1 });
	lpImageMng.GetID("�e", "image/bullet.png", { 30,30 }, { 1,1 });
	lpImageMng.GetID("�G����", "image/EWin.png", { 800,600 }, { 1,1 });
	lpImageMng.GetID("���@����", "image/PWin.png", { 800,600 }, { 1,1 });



	_objList.emplace_back(
		new Player({ 400, 300 }, { 0,0 })
	);

	_objList.emplace_back(
		new Aim({ 400, 200 }, { 0,0 })
	);

	_objList.emplace_back(
		new Enemy({ 400, 500 }, { 0,0 })
	);

	_objList.emplace_back(
		new EAim({ 400, 400 }, { 0,0 })
	);



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
	//if ((!lpSceneMng.PFlag) && (!lpSceneMng.EFlag))
	//{
		for (auto data : _objList)
		{
			(*data).Update(*plObj);
		}
	//}
	//}
	for (auto data : _objList)
	{
		/*data->Draw();*/
		//if (CheckHitKey(KEY_INPUT_SPACE))
		//{
		//	(*data).SetAlive(false);
		//}
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
		case ACT_QUE::SHOT:
			FuncBullet()(actQue, this);
			break;
		case ACT_QUE::CHECK_HIT:
			FuncCheckHit()(actQue, this);
			break;
		default:
			//AST();
			break;
		}
	}

}

