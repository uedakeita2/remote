#include <algorithm>
#include <DxLib.h>
#include "../_debug/_DebugConOut.h"
#include "GameScene.h"
#include "../common/imageMng.h"
#include "../Player.h"
#include "../Scene/SceneMng.h"

GameScene::GameScene()
{

	lpImageMng.GetID("���", "image/player.png", { 100,100 }, { 1,1 });

	_objList.emplace_back(
		new Player({ 0, 0 }, { 0,0 })
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

	if (!FadeUpdate())
	{
		for (auto data : _objList)
		{
			(*data).Update(*plObj);
		}
	}

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
}

