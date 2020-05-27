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


enum class DRAW_QUE // enumは型が曖昧 classをつけるとclass名＝名前空間だからXという名前が同じでも違うものになる 
{
	IMAGE,
	X,
	Y,
	RAD,
	ZORDER,		// ﾚｲﾔｰ内の描画順(数値内の低いほうが奥)
	LAYER,		// IDの小さいほうが奥に描画
	DRAW_MODE,	// 描画モード
	DRAW_NUM	// 描画モードに渡す値

};

//enum class LAYER // debuglayerは独立しているからいれない
//{
//	BG,
//	CHAR,
//	UI
//};

class Obj;

using DrawQueT = std::tuple<int, double, double, double, int, LAYER, int, int>; //  id,x,y,rad,ﾚｲﾔｰID,zOder(奥行のこと) DRAW_QUEの内容

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
		sInstance = nullptr; // ﾃﾞﾘｰﾄしてもｺﾞﾐがのこるからnullをいれる
	}

	void Run(void);

	// std::tuple<int, int, int> data1;
	// std::pair<int, double> data2;

	bool AddDrawQue(DrawQueT dQue);
	bool AddActQue(ActQueT aQue);

	const Vector2 ScreenSize;
	const Vector2 ScreenCenter;			// ｽｸﾘｰﾝの中心
	const Vector2 GameScreenSize;
	const Vector2 GameScreenOffset;		// ｹﾞｰﾑｴﾘｱの左上

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
	int frame;							// ﾌﾚｰﾑｶｳﾝﾄ用　EnemyMove(LR)で使用
	int cntFrame;						// enemyｶｳﾝﾄ用 EnemyMove(LR)で使用

private:
	static SceneMng* sInstance;

	unique_Base _activeScene;

	void Draw(void);

	int _layerGID;

	//std::map<LAYER , int> _screenID; // ｷｰ,　型 makeScreenで作ったものをセットする
	std::vector<DrawQueT> _drawList;
	std::vector<ActQueT> _actList;

	/*static int sFrame;*/

	~SceneMng();
	SceneMng();
	bool SysInit(void);



};

