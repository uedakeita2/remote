#pragma once
#include <functional>
#include <vector>
#include "BaseScene.h"
#include "../obj.h"
//#include <bullet.h>

struct FuncShake;
struct FuncBullet;
struct FuncCheckHit;


using funcAct = std::function<bool(ActQueT&, void*)>;	// ï¿Ç—Ç≥Ç¶Ç†Ç¡ÇƒÇÍÇŒÅAÇ»ÇÒÇ≈Ç‡ì¸ÇÍÇÁÇÍÇÈ

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;
private:
	friend FuncShake;
	friend FuncBullet;
	friend FuncCheckHit;
	std::vector<sharedObj> _objList;
	void RunActQue(std::vector<ActQueT> actList) override;
	std::map<ACT_QUE, funcAct> funcQue;
	sharedObj plObj;


};

