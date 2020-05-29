#include <algorithm>
#include "FuncBullet.h"
#include "../../bullet.h"
#include "../../Ebullet.h"
#include "../GameScene.h"
#include "../SceneMng.h"

//std::map<UNIT_ID, int> FuncBullet::_MaxCount{ { UNIT_ID::PL_BULLET,4} ,{ UNIT_ID::EM_BULLET,4} };

bool FuncBullet::operator()(ActQueT& actQue, void* scene)
{
	 PBullet = lpSceneMng.PBulletCnt;
	 EBullet = lpSceneMng.EBulletCnt;

	UNIT_ID unitID = (actQue.second.unitID() == UNIT_ID::PLAYER ? UNIT_ID::PL_BULLET : UNIT_ID::EM_BULLET);

	//if (_MaxCount[unitID] > std::count_if(((GameScene*)scene)->_objList.begin(), ((GameScene*)scene)->_objList.end(), [&](sharedObj obj) {return ((*obj).unitID() == unitID); }))
	if (PBullet > std::count_if(((GameScene*)scene)->_objList.begin(), ((GameScene*)scene)->_objList.end(), [&](sharedObj obj) {return ((*obj).unitID() == unitID); }))
	{
		if (unitID == UNIT_ID::PL_BULLET)
		{
			((GameScene*)scene)->_objList.emplace_back(
				new bullet(unitID, actQue.second.pos())		// 弾数制限をしていない　secondのposに座標が入っている　必要なUNIT_IDを指定する
			);
		}
	}
	if (EBullet > std::count_if(((GameScene*)scene)->_objList.begin(), ((GameScene*)scene)->_objList.end(), [&](sharedObj obj) {return ((*obj).unitID() == unitID); }))
	{
		if (unitID == UNIT_ID::EM_BULLET)
		{
			((GameScene*)scene)->_objList.emplace_back(
				new Ebullet(unitID, actQue.second.pos())		// 弾数制限をしていない　secondのposに座標が入っている　必要なUNIT_IDを指定する
			);
		}
	}
	return false;
}