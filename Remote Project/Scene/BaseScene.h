#pragma once
#include <memory>
#include "../obj.h"
#include <vector>

class BaseScene;		// ﾌﾟﾛﾄﾀｲﾌﾟ宣言

enum class ACT_QUE
{
	NON,		
	SHOT,
	CHECK_HIT,
	MAX
};

using unique_Base = std::unique_ptr<BaseScene>;
using ActQueT = std::pair<ACT_QUE, Obj&>;

class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;	// 絶対ないと困る
	virtual void RunActQue(std::vector<ActQueT> actList);	// ｺﾋﾟｰを作る 渡す側がmoveで渡す 仮想関数 純粋仮想関数ではない　必ずしも全部のｼｰﾝで必要というわけではないから
};


