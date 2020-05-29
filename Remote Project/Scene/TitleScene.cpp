#include <memory>
#include "TitleScene.h"
#include "GameScene.h"
#include "BaseScene.h"
#include <DxLib.h>
#include "SceneMng.h"
#include "CharSelScene.h"


TitleScene::TitleScene()
{
	lpImageMng.GetID("ю╡ды", "image/title.png");
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{
	lpSceneMng.AddDrawQue({ IMAGE_ID("ю╡ды")[0],400.0,300.0,0,0,LAYER::BG,DX_BLENDMODE_NOBLEND,255 });
	if (CheckHitKey(KEY_INPUT_Z))
	{
		return std::make_unique<CharSelScene>();
	}

	return std::move(own);
}
