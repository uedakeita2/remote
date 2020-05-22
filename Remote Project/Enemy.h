#pragma once
#include "Obj.h"
#include <memory>
#include "Input/InputState.h"
#include "Scene/SceneMng.h"
#include "Scene/BaseScene.h"
#include "DxLib.h"

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(Vector2Dbl pos, Vector2Dbl size);
	void Update(sharedObj plObj) override;
	~Enemy();
	void Draw(void);
	DINPUT_JOYSTATE _Input;
	bool KeyFlag;
	bool OldKeyFlag;
	int PadInput;
private:
	void Init(void);
	std::shared_ptr<InputState> _input;
};

