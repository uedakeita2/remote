#include "Enemy.h"
#include "common/imageMng.h"
#include "Scene/GameScene.h"
#include "Input/KeyState.h"
#include "DxLib.h"

Enemy::Enemy()
{
	_unitID = UNIT_ID::ENEMY;
	Init();
}

Enemy::Enemy(Vector2Dbl pos, Vector2Dbl size)
{
	_unitID = UNIT_ID::ENEMY;
	_pos = pos;
	_size = size;
	KeyFlag = false;
	OldKeyFlag = false;
	Init();
}

void Enemy::Update(sharedObj plObj)
{
	KeyFlag = false;
	PadInput = GetJoypadInputState(DX_INPUT_PAD2);

	if (DestroyPrpc())
	{
		return;
	}

	if ((_Input.Ry > 0) || ((PadInput & PAD_INPUT_8) != 0))
	{
		KeyFlag = true;
	}

	// (*_input).Update(); .�͒��@->�͊O
	_input->Update();
	/*if (_input->state(INPUT_ID::LEFT).first)
	{
		_pos.x -= 2;
	}*/

	auto move = [](std::weak_ptr<InputState> keyData, INPUT_ID id, double& pNum, const int speed) {
		// keyData.expired() �I����Ă��邩���Ȃ���
		if (!keyData.expired())
		{
			if ((*keyData.lock()).state(id).first)
			{
				pNum += speed;
			}
		}
	};

	//GetJoypadAnalogInput(&inputX, &inputY, DX_INPUT_KEY_PAD2);
	//if (inputX >0)
	//{
	//	_pos.x += 4;
	//}
	//if (inputX < 0)
	//{
	//	_pos.x -= 4;
	//}
	//if (inputY < 0)
	//{
	//	_pos.y -= 4;
	//}
	//if (inputY > 0)
	//{
	//	_pos.y += 4;
	//}

	// �p�b�h�̃L�[�����擾
	GetJoypadDirectInputState(DX_INPUT_PAD2, &_Input);
	if ((!lpSceneMng.PFlag) && (!lpSceneMng.EFlag))
	{
		if (_Input.X > 0)
		{
			_pos.x += 4;
		}
		if (_Input.X < 0)
		{
			_pos.x -= 4;
		}
		if (_Input.Y < 0)
		{
			_pos.y -= 4;
		}
		if (_Input.Y > 0)
		{
			_pos.y += 4;
		}

		// �{�^�����������Ƃ������e�𔭎˂�����
		if ((_Input.Ry > 0)|| ((PadInput & PAD_INPUT_8) != 0))
		{
			if ((!OldKeyFlag) && (KeyFlag))
			{
				lpSceneMng.AddActQue({ ACT_QUE::SHOT,*this });
			}
		}
		// �L�[�{�[�h�ړ�����
		move(_input, INPUT_ID::LEFT, _pos.x, -2);
		move(_input, INPUT_ID::RIGHT, _pos.x, 2);
		move(_input, INPUT_ID::UP, _pos.y, -2);
		move(_input, INPUT_ID::DOWN, _pos.y, 2);

		//if ((*_input).state(INPUT_ID::BTN_1).first && !(*_input).state(INPUT_ID::BTN_1).second)
		//{
		//	lpSceneMng.AddActQue({ ACT_QUE::SHOT,*this });
		//}
		lpSceneMng._Epos = _pos;
		OldKeyFlag = KeyFlag;
	}
	if (lpSceneMng.EFlag)
	{
		lpSceneMng.AddDrawQue({ IMAGE_ID("�G����")[0],400.0,300.0,0,0,LAYER::UI ,DX_BLENDMODE_NOBLEND,255 });
	}
	return;
}


Enemy::~Enemy()
{
}

void Enemy::Draw(void)
{
	Obj::Draw();
}

void Enemy::Init(void)
{
	AnimVector data;
	data.emplace_back(IMAGE_ID("���")[lpSceneMng.EnemyNo], 30);
	SetAnim(STATE::NORMAL, data);


	_input = std::make_shared<KeyState>();
	// _input.reset(new KeyState()); 



	state(STATE::NORMAL);

}


