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
	Vector2Dbl _length;			// �Ə��܂ł̒���
	Vector2Dbl _vector;			// �e�̃x�N�g��
	Vector2Dbl _speed;			// �X�s�[�h
	Vector2 VectorSwitch;		// �e�̔��˂̐؂�ւ�
	Vector2 boundCnt;			// �e�̔��˃J�E���g
	float BulletSpeed;
private:
	void Init(void);
	bool DestroyProc(void);
};

