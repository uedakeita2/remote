#pragma once
#include "Obj.h"
#include <memory>
#include "Input/InputState.h"
#include "Scene/SceneMng.h"
#include "Scene/BaseScene.h"
#include "DxLib.h"
#include "bullet.h"

struct bullet;
class Aim :
	public Obj
{
public:

	Aim();
	Aim(Vector2Dbl pos, Vector2Dbl size);
	void Update(sharedObj plObj) override;
	~Aim();
	void Draw(void);
	DINPUT_JOYSTATE _Input;
	Vector2Dbl _plPos;
private:
	friend class bullet;
	void Init(void);
	std::shared_ptr<InputState> _input;
	Vector2Dbl plPos;			// obj‚Ìposî•ñŠi”[•Ï”

};

