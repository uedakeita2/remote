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

	// (*_input).Update(); .は中　->は外
	_input->Update();
	/*if (_input->state(INPUT_ID::LEFT).first)
	{
		_pos.x -= 2;
	}*/

	auto move = [](std::weak_ptr<InputState> keyData, INPUT_ID id, double& pNum, const int speed) {
		// keyData.expired() 終わっているかいないか
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

	// パッドのキー情報を取得
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

		// ボタンを押したときだけ弾を発射させる
		if ((_Input.Ry > 0)|| ((PadInput & PAD_INPUT_8) != 0))
		{
			if ((!OldKeyFlag) && (KeyFlag))
			{
				lpSceneMng.AddActQue({ ACT_QUE::SHOT,*this });
			}
		}
		// キーボード移動処理
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
		lpSceneMng.AddDrawQue({ IMAGE_ID("敵勝利")[0],400.0,300.0,0,0,LAYER::UI ,DX_BLENDMODE_NOBLEND,255 });
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
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[lpSceneMng.EnemyNo], 30);
	SetAnim(STATE::NORMAL, data);


	_input = std::make_shared<KeyState>();
	// _input.reset(new KeyState()); 



	state(STATE::NORMAL);

}


