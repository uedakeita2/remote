#pragma once
#include <memory>
#include "../obj.h"
#include <vector>

class BaseScene;		// ÌßÛÄÀ²ÌßéŒ¾

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
	virtual unique_Base Update(unique_Base own) = 0;	// â‘Î‚È‚¢‚Æ¢‚é
	virtual void RunActQue(std::vector<ActQueT> actList);	// ºËß°‚ğì‚é “n‚·‘¤‚ªmove‚Å“n‚· ‰¼‘zŠÖ” ƒˆ‰¼‘zŠÖ”‚Å‚Í‚È‚¢
	Vector2 _screenPos;

};


