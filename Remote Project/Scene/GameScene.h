#pragma once
#include <functional>
#include <vector>
#include "BaseScene.h"
#include "../Obj.h"
//#include <bullet.h>

struct FuncShake;
struct FuncBullet;
struct FuncCheckHit;


using funcAct = std::function<bool(ActQueT&, void*)>;	// 並びさえあってれば、なんでも入れられる

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;
private:
	friend FuncBullet;
	friend FuncCheckHit;
	//void initFunc(void);
	std::vector<sharedObj> _objList;
	void RunActQue(std::vector<ActQueT> actList) override;
	std::map<ACT_QUE, funcAct> funcQue;
	sharedObj plObj;

};

