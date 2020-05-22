#include "FuncCheckHit.h"
#include "../../bullet.h"
#include "../../Ebullet.h"
#include "../../Obj.h"
#include "../GameScene.h"


bool FuncCheckHit::operator()(ActQueT& actQue, void* scene)
{
	UNIT_ID unitID = (actQue.second.unitID() == UNIT_ID::PL_BULLET ? UNIT_ID::PLAYER : UNIT_ID::ENEMY);

	for (auto data : ((GameScene*)scene)->_objList)
	{
		if ((*data).unitID() != UNIT_ID::PL_BULLET && (*data).unitID() != UNIT_ID::EM_BULLET)
		{
			if (((*data).unitID() != unitID) && ((*data).unitID() != UNIT_ID::NON))
			{
				if (abs(actQue.second.pos().y - (*data).pos().y) <= actQue.second.size().y + (*data).size().y &&
					abs(actQue.second.pos().x - (*data).pos().x) <= actQue.second.size().x + (*data).size().x)
				{
					(*data).SetAlive(false);
					actQue.second.SetAlive(false);
					if (actQue.second.unitID() == UNIT_ID::PL_BULLET)
					{
						// Enemy‚É’e‚ª“–‚½‚Á‚½
						lpSceneMng.ELife--;
						if (lpSceneMng.ELife == 0)
						{
							lpSceneMng.PFlag = true;
						}
					}
					if (actQue.second.unitID() == UNIT_ID::EM_BULLET)
					{
						// Player‚É’e‚ª“–‚½‚Á‚½
						lpSceneMng.PLife--;
						if (lpSceneMng.PLife == 0)
						{
							lpSceneMng.EFlag = true;
						}
					}
					lpSceneMng.cntFrame++;
				}
			}
		}
	}

	return false;
}

