#pragma once
#include "Obj.h"
#include "Scene/SceneMng.h"
#include "Scene/BaseScene.h"
#include <memory>
#include "Aim.h"


class bullet :
	public Obj
{
public:
	bullet();
	bullet(UNIT_ID unitID, Vector2Dbl pos);
	void Update(sharedObj plObj) override;
	~bullet();
	Vector2Dbl _length;			// 照準までの長さ
	Vector2Dbl _vector;			// 弾のベクトル
	Vector2Dbl _speed;			// スピード
	Vector2 VectorSwitch;		// 弾の反射の切り替え
	Vector2 boundCnt;			// 弾の反射カウント
	float BulletSpeed;
private:
	void Init(void);
	bool DestroyProc(void);
};

