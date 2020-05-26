#include "CharSelScene.h"
#include "DxLib.h"
#include "GameScene.h"
#include "SceneMng.h"

CharSelScene::CharSelScene()
{

}

CharSelScene::~CharSelScene()
{
}

unique_Base CharSelScene::Update(unique_Base own)
{
	PadInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	EPadInput = GetJoypadInputState(DX_INPUT_PAD2);

	if (CheckHitKey(KEY_INPUT_Z))
	{
		return std::make_unique<GameScene>();
	}

	return std::move(own);
}
