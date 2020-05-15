#include <Dxlib.h>
#include "SceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"
#include <algorithm>

SceneMng* SceneMng::sInstance = nullptr;

SceneMng::SceneMng() :ScreenSize{ 800.0,600.0 }, ScreenCenter{ ScreenSize / 2 }, GameScreenSize{ 500.0,390.0 }, GameScreenOffset{ (ScreenSize - GameScreenSize) / 2 }// �ݽ�׸����������u�ԁAۯ���������B
{
	/*sFrame = 0;*/
	frame = 0;
	cntFrame = 0;
}


void SceneMng::Draw(void)
{
	// layerID��sort����@�����_�����g��

	std::sort(_drawList.begin(), _drawList.end(),
		[](DrawQueT dQueA, DrawQueT dQueB) {		// sort���邽�߂ɂ͓�̏�񂪕K�v�������̵�޼ު�Ă�p�ӂ���
			return
				std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueA), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueA))
				<
				std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueB), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueB)); // zOrder���������قǑO�ɒu��
		});

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	LAYER drawLayer = begin(LAYER());
	int blendMode = DX_BLENDMODE_NOBLEND;
	int blendModeNum = 255;

	SetDrawScreen(_layerGID);
	ClsDrawScreen();
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	SetDrawBlendMode(blendMode, blendModeNum);


	/*SetDrawScreen(_screenID[LAYER::BG]); // ��񂸂¸ر���Ȃ��Ɣ����̍ŏI�ڰт��c��
	ClsDrawScreen();
	SetDrawScreen(_screenID[LAYER::CHAR);
	ClsDrawScreen();
	SetDrawScreen(_screenID[LAYER::UI]);
	ClsDrawScreen();*/


	// �����ɂ��܂��Ă���Que��`�悷��
	for (auto dQue : _drawList)	// get���g�������@���ʂ�����
	{
		double x, y, rad;
		int id;
		LAYER layer;

		int blendModeOld = blendMode;
		int blendModeNumOld = blendModeNum;

		std::tie(id, x, y, rad, std::ignore, layer, blendMode, blendModeNum) = dQue;		// ���������ׂɎ��o�� ignore �K�v�̂Ȃ����̂�ǂݔ�΂�

		//if (_screenID[layer] != GetDrawScreen())	// ���������Ă��邩�킩��Ȃ��̂Ŋ�Ȃ�
		//{
		//	SetDrawScreen(_screenID[layer]);
		//}

		if ((layer != drawLayer) || (blendModeOld != blendMode) || (blendModeNum != blendModeNumOld))
		{
			// _layerGID�ɏ��������e���o�b�N�o�b�t�@�ɕ`�悷��
			SetDrawScreen(DX_SCREEN_BACK);
			SetDrawBlendMode(blendModeOld, blendModeNumOld);
			auto layPos = ScreenCenter + (*_activeScene)._screenPos;
			DrawRotaGraph(layPos.x, layPos.y, 1.0, 0, _layerGID, true);

			// ����Que�̂��߂̏��������A�s������ꎞ�`���ɐݒ肷��
			SetDrawScreen(_layerGID);
			SetDrawBlendMode(blendMode, blendModeNum);
			ClsDrawScreen();
		}

		DrawRotaGraph(
			static_cast<int>(x),
			static_cast<int>(y),
			1.0,
			rad,
			id,
			true);

		/*DrawRotaGraph(
			static_cast<int>(std::get<static_cast<int>(DRAW_QUE::X)>(dQue)),
			static_cast<int>(std::get<static_cast<int>(DRAW_QUE::Y)>(dQue)),
			1.0,
			std::get<static_cast<int>(DRAW_QUE::RAD)>(dQue),
			std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue),
			true);	*/

	}
	//for (int no = 0; no < _drawList.size(); no++)	// size�ŗv�f��������
	//{
	//	// _drawList[no];// �����DRAW_QUE���Ƃ��
	//		DrawGraph(
	//			std::get<static_cast<int>(DRAW_QUE::X)>(_drawList[no]),
	//			std::get<static_cast<int>(DRAW_QUE::Y)>(_drawList[no]),
	//			std::get<static_cast<int>(DRAW_QUE::IMAGE)>(_drawList[no]),
	//			true);
	//}
	//{

	//}
	//for(auto dQue = _drawList.begin(); dQue != _drawList.end(); dQue++) // ��ڰ���auto���g��
	//{
	//	DrawGraph(
	//	    std::get<static_cast<int>(DRAW_QUE::X)>(*dQue),
	//		std::get<static_cast<int>(DRAW_QUE::Y)>(*dQue),
	//		std::get<static_cast<int>(DRAW_QUE::IMAGE)>(*dQue),
	//		true);
	//}
	// ��ʂɏo�����߂�Draw

	// for���𔲂���Ō��_layerGID�̓��e���o�b�N�o�b�t�@�ɏ����o��
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawBlendMode(blendMode, blendModeNum);
	DrawRotaGraph(ScreenCenter.x, ScreenCenter.y, 1.0, 0, _layerGID, true);

	ScreenFlip();

}

SceneMng::~SceneMng()
{

}

void SceneMng::Run(void)
{
	SysInit();
	_activeScene = std::make_unique<GameScene>();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{

		_drawList.clear();
		AddDrawQue({ IMAGE_ID("�g")[0],400.0,300.0,0,0,LAYER::BG,DX_BLENDMODE_NOBLEND,255 });
		_activeScene = (*_activeScene).Update(std::move(_activeScene));	// move���g�����ƂŃR�s�[����炸�ɏ��L���̏��n���ł���
		// �X�}�[�g�|�C���^�Ƃ��Ă킩��₷���̂���@_activeScene->Update();
		// �����Ŕ�΂�ACT
		(*_activeScene).RunActQue(std::move(_actList));	// �ر���K�v���ǂ����𔻒f����

		Draw();
		frame++;

	}

}

bool SceneMng::AddDrawQue(DrawQueT dQue)
{
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) <= 0) 	// std::get<���Ԗ�>�Ŏ��o��
	{
		// �摜ID���s���Ȃ̂ŁA�ǉ����Ȃ�
		return false;
	}
	// Que��ǉ�
	// _drawList.push_back(); �v�f��ǉ�����Ƃ��Ɏg��

	_drawList.emplace_back(dQue);
	return true;
}

bool SceneMng::AddActQue(ActQueT aQue)
{
	_actList.emplace_back(aQue);

	return true;
}


bool SceneMng::SysInit(void)
{
	//���я���
	SetWindowText("Remote");
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);				// 800*600�ޯāA65536�FӰ�ނɐݒ�
	ChangeWindowMode(true);										// true:window  false:�ٽ�ذ�
	if (DxLib_Init() == -1)										// DXײ���؂̏�����
	{
		return false;												// DxLibײ���؏���������
	}

	SetDrawScreen(DX_SCREEN_BACK);	// �`�����ޯ��ޯ̧�ɐݒ�

	_layerGID = MakeScreen(ScreenSize.x, ScreenSize.y, true);

	//_debSetUP(200);

	lpImageMng.GetID("�g", "image/frame.png");
	lpImageMng.GetID("black", "image/black.png");
	lpImageMng.GetID("white", "image/white.png");

	return false;
}
