#include "common/imageMng.h"
#include "bullet.h"
#include "Aim.h"



bullet::bullet()
{
	Init();
}

bullet::bullet(UNIT_ID unitID, Vector2Dbl pos)
{
	_unitID = unitID;
	_pos = pos;
	_size = { 30,30 };
	_rad = 0;
	VectorSwitch = { 1,1 };
	boundCnt = { 0,0 };
	_length = lpSceneMng._aimPos - _pos;
	Init();
}


void bullet::Update(sharedObj plObj)
{
	if (bullet::DestroyProc())
	{
		return;
	}
	//  座標を更新
	_rad = atan2(_length.y, _length.x);
	_vector.x = cos(_rad) * 10;
	_vector.y = sin(_rad) * 10;
	if ((_pos.x >= 800) || (_pos.x <= 0))
	{
		boundCnt.x++;
		if (boundCnt.x % 2 == 1)
		{
			VectorSwitch.x = -1;
		}
		else
		{
			VectorSwitch.x = 1;
		}
	}
	if ((_pos.y >= 600) || (_pos.y <= 0))
	{
		boundCnt.y++;
		if (boundCnt.y % 2 == 1)
		{
			VectorSwitch.y = -1;
		}
		else
		{
			VectorSwitch.y = 1;
		}
	}
	_pos.x += _vector.x * VectorSwitch.x;
	_pos.y += _vector.y * VectorSwitch.y;
	//_vector = sqrt(_length.x * _length.x + _length.y * _length.y);
	//_speed.x = _length.x / _vector;
	//_speed.y = _length.y / _vector;
	//_pos.x += _speed.x * 10.0;
	//_pos.y += _speed.y * 10.0;
	lpSceneMng.AddActQue({ ACT_QUE::CHECK_HIT ,*this });

}

bullet::~bullet()
{
}

void bullet::Init(void)
{
	AnimVector data;

	data.emplace_back(IMAGE_ID("弾")[0], 30);
	SetAnim(STATE::NORMAL, data);

	data.reserve(1);
	data.emplace_back(-1, 40);		// -1 ロードグラフの使用で-1にしている
	SetAnim(STATE::DETH, data);

	state(STATE::NORMAL);
	return;
}

bool bullet::DestroyProc(void)
{
	// bullet独自の死亡判定　画面外判定
	// objのデストロイプﾛｯｸを呼ぶ
	if (Obj::DestroyPrpc())
	{
		return true;
	}

	if (boundCnt.x + boundCnt.y >= 4)
	{
		SetAlive(false);
	}

	if (lpSceneMng.EFlag)
	{
		SetAlive(false);
	}

	return false;
}
