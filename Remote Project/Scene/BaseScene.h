#pragma once
#include <memory>
#include "../obj.h"
#include <vector>

class BaseScene;		// �������ߐ錾

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
	virtual unique_Base Update(unique_Base own) = 0;	// ��΂Ȃ��ƍ���
	virtual void RunActQue(std::vector<ActQueT> actList);	// ��߰����� �n������move�œn�� ���z�֐� �������z�֐��ł͂Ȃ��@�K�������S���̼�݂ŕK�v�Ƃ����킯�ł͂Ȃ�����
};


