#pragma once
#include "Obj.h"
#include <memory>
#include "Input/InputState.h"
#include "Scene/SceneMng.h"
#include "Scene/BaseScene.h"
#include "DxLib.h"

class Player :
	public Obj
{
public:
	Player();
	Player(Vector2Dbl pos, Vector2Dbl size);
	void Update(sharedObj plObj) override;
	~Player();
	void Draw(void);
	int _glowID;
	DINPUT_JOYSTATE _Input;
	bool KeyFlag;
	bool OldKeyFlag;
	int PadInput;
private:
	void Init(void);
	std::shared_ptr<InputState> _input;
};

