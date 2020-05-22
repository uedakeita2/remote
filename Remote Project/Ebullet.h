#pragma once
#include "Obj.h"
#include "Scene/SceneMng.h"
#include "Scene/BaseScene.h"
#include <memory>
#include "EAim.h"


class Ebullet :
	public Obj
{
public:
	Ebullet();
	Ebullet(UNIT_ID unitID, Vector2Dbl pos);
	void Update(sharedObj plObj) override;
	~Ebullet();
	Vector2Dbl _length;			// 照準までの長さ
	Vector2Dbl _vector;			// 弾のベクトル
	Vector2Dbl _speed;			// スピード
	Vector2 VectorSwitch;		// 弾の反射の切り替え
	Vector2 boundCnt;			// 弾の反射カウント
private:
	void Init(void);
	bool DestroyProc(void);
};

