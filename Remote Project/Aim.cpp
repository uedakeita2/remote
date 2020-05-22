#include "Aim.h"
#include "common/imageMng.h"
#include "Player.h"
#include "Scene/GameScene.h"
#include "Input/KeyState.h"
#include <DxLib.h>


Aim::Aim()
{
	_unitID = UNIT_ID::NON;
	Init();
}

Aim::Aim(Vector2Dbl pos, Vector2Dbl size)
{
	_unitID = UNIT_ID::NON;
	_pos = pos;
	_size = size;
	Init();
}

void Aim::Update(sharedObj plObj)
{

	// ここでposをコピーする
	plPos = (*plObj).pos();
	lpSceneMng._aimPos = _pos;
	if (DestroyPrpc())
	{
		return;
	}

	_input->Update();

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


	// パッドのキー情報を取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &_Input);
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

		// 400はプレイヤーの座標
		_pos.x = _Input.Z / 8 + plPos.x;
	}




	move(_input, INPUT_ID::LEFT, _pos.x, -2);
	move(_input, INPUT_ID::RIGHT, _pos.x, 2);
	move(_input, INPUT_ID::UP, _pos.y, -2);
	move(_input, INPUT_ID::DOWN, _pos.y, 2);

	if ((*_input).state(INPUT_ID::BTN_1).first && !(*_input).state(INPUT_ID::BTN_1).second)
	{
		lpSceneMng.AddActQue({ ACT_QUE::SHOT,*this });
	}
	return;
}


Aim::~Aim()
{
}

void Aim::Draw(void)
{
	Obj::Draw();
}

void Aim::Init(void)
{
	AnimVector data;
	data.emplace_back(IMAGE_ID("照準")[0], 30);
	SetAnim(STATE::NORMAL, data);


	_input = std::make_shared<KeyState>();

	state(STATE::NORMAL);

}



