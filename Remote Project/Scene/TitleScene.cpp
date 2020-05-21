#include <memory>
#include "TitleScene.h"
#include "GameScene.h"
#include "BaseScene.h"
#include <DxLib.h>
#include "SceneMng.h"


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{
	if (CheckHitKey(KEY_INPUT_Z))
	{
		return std::make_unique<GameScene>();
	}

	return std::move(own);
}
