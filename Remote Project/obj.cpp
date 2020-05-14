#include <DxLib.h>
#include "Obj.h"
#include "Scene/SceneMng.h"
#include "common/imageMng.h"


Obj::Obj()
{
	_alive = true;
	_dead = false;
	_animFrame = 0;
	_animCount = 0;
	_rad = 0;
	_zOrder = 100;
	_unitID = UNIT_ID::NON;
}


void Obj::Draw(void)
{
	if (_animMap.find(_state) == _animMap.end()) // �����������ڰ���Ԃ��@end�܂ŗ���Ƃ������Ƃ́A�����ް������݂��Ȃ��Ƃ�������
	{
		return;
	}
	if (_animFrame < 0 || _animFrame >= _animMap[_state].size()) // �v�f���𒲂ׂ�Ƃ��A�擾���鎞��size���g��
	{
		return;
	}

	// _animMap[_animKey].size() �R�}��

	if (_animMap[_state][_animFrame].first >= 0)
	{
		if (_animCount >= _animMap[_state][_animFrame].second)
		{
			_animFrame++;
		}

		_animCount++;

		if (_animFrame >= _animMap[_state].size())
		{
			_animFrame = 0;
			_animCount = 0;
		}

		lpSceneMng.AddDrawQue({ _animMap[_state][_animFrame].first,_pos.x + lpSceneMng.GameScreenOffset.x,_pos.y + lpSceneMng.GameScreenOffset.y , _rad , _zOrder, LAYER::CHAR , DX_BLENDMODE_NOBLEND,255 });
	}
}

void Obj::Draw(int id)
{
	lpSceneMng.AddDrawQue({ id,_pos.x + lpSceneMng.GameScreenOffset.x,_pos.y + lpSceneMng.GameScreenOffset.y, _rad , _zOrder, LAYER::CHAR , DX_BLENDMODE_NOBLEND,255 });
}


Obj::~Obj()
{
}

bool Obj::state(const STATE state)
{
	if (_animMap.find(state) == _animMap.end())
	{
		return false;
	}

	if (_state != state)
	{
		_animFrame = 0;
		_animCount = 0;
	}

	_state = state;
	return true;
}

const STATE Obj::state(void) const
{
	return _state;
}

const Vector2Dbl& Obj::pos(void) const
{
	return _pos;
}

const Vector2Dbl& Obj::size(void) const
{
	return _size;
}

UNIT_ID Obj::unitID()
{
	return _unitID;
}



bool Obj::SetAnim(const STATE state, AnimVector& data)
{
	return (_animMap.try_emplace(state, std::move(data))).second; // first iterator���Ԃ� second bool�l���Ԃ�@17�ȍ~�����g���Ȃ�
	// emplace �V�K���ް�����͂��� try���Ăق����L�[�@�g���C��������


	/*if (_animMap.find(Key) == _animMap.end())
	{
		_animMap[Key] = data;
		return true;
	}

	return false;*/
}

bool Obj::SetAlive(bool alive)
{
	_alive = alive;
	if (!_alive)
	{
		state(STATE::DETH);
	}

	return true;
}

bool Obj::isAnimEnd(void)
{
	// _animMap[_state][_animFrame].first >= 0
	if (_animMap.find(_state) == _animMap.end()) // �����������ڰ���Ԃ��@end�܂ŗ���Ƃ������Ƃ́A�����ް������݂��Ȃ��Ƃ�������
	{
		return true;
	}
	if (_animFrame < 0 || _animFrame >= _animMap[_state].size()) // �v�f���𒲂ׂ�Ƃ��A�擾���鎞��size���g��
	{
		return true;
	}


	if (_animMap[_state][_animFrame].first == -1)
	{
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

bool Obj::DestroyPrpc(void) // �j�����Ă������̊m�F
{
	if (_alive)
	{
		return false;
	}
	if (isAnimEnd())
	{
		_dead = true;
	}

	return true;
}
