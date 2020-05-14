#include <algorithm>
#include <DxLib.h>
#include "../_debug/_DebugConOut.h"
#include "GameScene.h"
#include "../common/imageMng.h"
#include "../Player.h"
#include "../Scene/SceneMng.h"

GameScene::GameScene()
{

	lpImageMng.GetID("ｷｬﾗ", "image/player.png", { 100,100 }, { 1,1 });

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
		_objList.begin(),	// ﾁｪｯｸ範囲の開始
		_objList.end(),		// ﾁｪｯｸ範囲の終了
		[](sharedObj& obj) {return(*obj).isDead(); } 	// 死んでるやつを除外 ここは真偽を必ず返す(プレディケート)
	);
	// itr 消したい要素の先頭アドレス
	_objList.erase(itr, _objList.end());

	//_objList.erase(std::remove_if(
	//					_objList.begin(),	// ﾁｪｯｸ範囲の開始
	//					_objList.end(),		// ﾁｪｯｸ範囲の終了
	//					[](sharedObj& obj) {return(*obj).isDead(); } 	// 死んでるやつを除外 ここは真偽を必ず返す(プレディケート)
	//				),
	//	_objList.end());



	return std::move(own);
}


void GameScene::RunActQue(std::vector<ActQueT> actList)
{
}

