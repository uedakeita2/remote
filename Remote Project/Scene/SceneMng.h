#pragma once
#include <memory>
#include <tuple> 
#include "../common/Vector2.h"
#include "BaseScene.h"
#include "../common/imageMng.h"
#include "../Obj.h"
#include <vector>
#include <map>
#include "LAYER_ID.h"


enum class DRAW_QUE // enum�͌^���B�� class�������class�������O��Ԃ�����X�Ƃ������O�������ł��Ⴄ���̂ɂȂ� 
{
	IMAGE,
	X,
	Y,
	RAD,
	ZORDER,		// ڲ԰���̕`�揇(���l���̒Ⴂ�ق�����)
	LAYER,		// ID�̏������ق������ɕ`��
	DRAW_MODE,	// �`�惂�[�h
	DRAW_NUM	// �`�惂�[�h�ɓn���l

};

//enum class LAYER // debuglayer�͓Ɨ����Ă��邩�炢��Ȃ�
//{
//	BG,
//	CHAR,
//	UI
//};

class Obj;

using DrawQueT = std::tuple<int, double, double, double, int, LAYER, int, int>; //  id,x,y,rad,ڲ԰ID,zOder(���s�̂���) DRAW_QUE�̓��e

#define lpSceneMng SceneMng::GetInstance()



class SceneMng
{
public:
	static SceneMng& GetInstance(void)
	{
		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr; // ��ذĂ��Ă��Ђ��̂��邩��null�������
	}

	void Run(void);

	// std::tuple<int, int, int> data1;
	// std::pair<int, double> data2;

	bool AddDrawQue(DrawQueT dQue);
	bool AddActQue(ActQueT aQue);

	const Vector2 ScreenSize;
	const Vector2 ScreenCenter;			// ��ذ݂̒��S
	const Vector2 GameScreenSize;
	const Vector2 GameScreenOffset;		// �ްѴر�̍���

	Vector2Dbl _aimPos;
	Vector2Dbl _EaimPos;
	Vector2Dbl _Epos;
	bool PFlag;
	bool EFlag;
	int PLife;
	int ELife;
	int EnemyNo;
	int PlayerNo;
	/*bool isFrame(void) { return sFrame; }*/
	int frame;							// �ڰѶ��ėp�@EnemyMove(LR)�Ŏg�p
	int cntFrame;						// enemy���ėp EnemyMove(LR)�Ŏg�p

private:
	static SceneMng* sInstance;

	unique_Base _activeScene;

	void Draw(void);

	int _layerGID;

	//std::map<LAYER , int> _screenID; // ��,�@�^ makeScreen�ō�������̂��Z�b�g����
	std::vector<DrawQueT> _drawList;
	std::vector<ActQueT> _actList;

	/*static int sFrame;*/

	~SceneMng();
	SceneMng();
	bool SysInit(void);



};

