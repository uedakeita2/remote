#include <DxLib.h>
#include "BaseScene.h"
#include "SceneMng.h"
#include "../common/imageMng.h"


BaseScene::BaseScene()
{
	_fadeScrID = MakeScreen(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, false);
	FadeInit("white");
}


BaseScene::~BaseScene()
{
}

void BaseScene::RunActQue(std::vector<ActQueT> actList)
{
	actList.clear();	// ﾀﾞﾐｰで入れる
}

void BaseScene::FadeInit(std::string fadeType)
{
	GetDrawScreenGraph(0, 0, lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, _fadeScrID);	// ｷｬﾌﾟﾁｬｰする

	_fadeCount = 510;
	_fadeType = fadeType;
}

bool BaseScene::FadeUpdate(void)// 毎ﾌﾚｰﾑ読む
{
	if (_fadeCount)
	{
		if (_fadeCount > 255)
		{
			lpSceneMng.AddDrawQue({ _fadeScrID , lpSceneMng.ScreenCenter.x , lpSceneMng.ScreenCenter.y,0,0,LAYER::EX,DX_BLENDMODE_NOBLEND,255 });

		}
		lpSceneMng.AddDrawQue({ lpImageMng.GetID(_fadeType)[0] , lpSceneMng.ScreenCenter.x , lpSceneMng.ScreenCenter.y,0,10,LAYER::EX,DX_BLENDMODE_ALPHA,255 - std::abs(_fadeCount - 255) });
		_fadeCount--;
	}

	return _fadeCount;
}
