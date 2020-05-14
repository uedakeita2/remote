#pragma once
#include <memory>
#include "../Obj.h"

class BaseScene;		// �������ߐ錾

enum class ACT_QUE
{
	NON,		// �������Ȃ��@��  ���炩�̗��R�łO�������Ă����ꍇ�Ashot���O�ɂȂ��Ă�Ɩ����ɂł邩�炻�̂��߂�NON������
	SHOT,
	CHECK_HIT,
	SHAKE,	// ����
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
	Vector2 _screenPos;

protected:
	void FadeInit(std::string fadeType);
	bool FadeUpdate(void);

private:
	int _fadeScrID;
	int _fadeCount;
	std::string _fadeType;
};

