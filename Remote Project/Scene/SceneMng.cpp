#include <Dxlib.h>
#include "SceneMng.h"
#include "GameScene.h"
#include "TitleScene.h"
#include <algorithm>

SceneMng* SceneMng::sInstance = nullptr;

SceneMng::SceneMng() :ScreenSize{ 800.0,600.0 }, ScreenCenter{ ScreenSize / 2 }, GameScreenSize{ 500.0,390.0 }, GameScreenOffset{ (ScreenSize - GameScreenSize) / 2 }// ｺﾝｽﾄﾗｸﾀが走った瞬間、ﾛｯｸがかかる。
{
	/*sFrame = 0;*/
	frame = 0;
	cntFrame = 0;
}


void SceneMng::Draw(void)
{
	// layerIDをsortする　ラムダ式を使う

	std::sort(_drawList.begin(), _drawList.end(),
		[](DrawQueT dQueA, DrawQueT dQueB) {		// sortするためには二つの情報が必要だから二つのｵﾌﾞｼﾞｪｸﾄを用意する
			return
				std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueA), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueA))
				<
				std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueB), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueB)); // zOrderが小さいほど前に置く
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


	/*SetDrawScreen(_screenID[LAYER::BG]); // 一回ずつｸﾘｱしないと爆発の最終ﾌﾚｰﾑが残る
	ClsDrawScreen();
	SetDrawScreen(_screenID[LAYER::CHAR);
	ClsDrawScreen();
	SetDrawScreen(_screenID[LAYER::UI]);
	ClsDrawScreen();*/


	// ｽﾀｯｸにたまっているQueを描画する
	for (auto dQue : _drawList)	// getを使いすぎ　無駄が多い
	{
		double x, y, rad;
		int id;
		LAYER layer;

		int blendModeOld = blendMode;
		int blendModeNumOld = blendModeNum;

		std::tie(id, x, y, rad, std::ignore, layer, blendMode, blendModeNum) = dQue;		// 情報をﾊﾞﾗﾊﾞﾗに取り出す ignore 必要のないものを読み飛ばす

		//if (_screenID[layer] != GetDrawScreen())	// 何が入っているかわからないので危ない
		//{
		//	SetDrawScreen(_screenID[layer]);
		//}

		if ((layer != drawLayer) || (blendModeOld != blendMode) || (blendModeNum != blendModeNumOld))
		{
			// _layerGIDに書いた内容をバックバッファに描画する
			SetDrawScreen(DX_SCREEN_BACK);
			SetDrawBlendMode(blendModeOld, blendModeNumOld);
			auto layPos = ScreenCenter + (*_activeScene)._screenPos;
			DrawRotaGraph(layPos.x, layPos.y, 1.0, 0, _layerGID, true);

			// 次のQueのための初期化し、行が先を一時描画先に設定する
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
	//for (int no = 0; no < _drawList.size(); no++)	// sizeで要素数が取れる
	//{
	//	// _drawList[no];// これでDRAW_QUEをとれる
	//		DrawGraph(
	//			std::get<static_cast<int>(DRAW_QUE::X)>(_drawList[no]),
	//			std::get<static_cast<int>(DRAW_QUE::Y)>(_drawList[no]),
	//			std::get<static_cast<int>(DRAW_QUE::IMAGE)>(_drawList[no]),
	//			true);
	//}
	//{

	//}
	//for(auto dQue = _drawList.begin(); dQue != _drawList.end(); dQue++) // ｲﾃﾚｰﾀはautoを使う
	//{
	//	DrawGraph(
	//	    std::get<static_cast<int>(DRAW_QUE::X)>(*dQue),
	//		std::get<static_cast<int>(DRAW_QUE::Y)>(*dQue),
	//		std::get<static_cast<int>(DRAW_QUE::IMAGE)>(*dQue),
	//		true);
	//}
	// 画面に出すためのDraw

	// for文を抜ける最後の_layerGIDの内容をバックバッファに書き出す
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
		AddDrawQue({ IMAGE_ID("枠")[0],400.0,300.0,0,0,LAYER::BG,DX_BLENDMODE_NOBLEND,255 });
		_activeScene = (*_activeScene).Update(std::move(_activeScene));	// moveを使うことでコピーを作らずに所有権の譲渡ができる
		// スマートポインタとしてわかりやすいのが上　_activeScene->Update();
		// ここで飛ばすACT
		(*_activeScene).RunActQue(std::move(_actList));	// ｸﾘｱが必要かどうかを判断する

		Draw();
		frame++;

	}

}

bool SceneMng::AddDrawQue(DrawQueT dQue)
{
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) <= 0) 	// std::get<何番目>で取り出す
	{
		// 画像IDが不正なので、追加しない
		return false;
	}
	// Queを追加
	// _drawList.push_back(); 要素を追加するときに使う

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
	//ｼｽﾃﾑ処理
	SetWindowText("Remote");
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);				// 800*600ﾄﾞｯﾄ、65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);										// true:window  false:ﾌﾙｽｸﾘｰﾝ
	if (DxLib_Init() == -1)										// DXﾗｲﾌﾞﾗﾘの初期化
	{
		return false;												// DxLibﾗｲﾌﾞﾗﾘ初期化処理
	}

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先をﾊﾞｯｸﾊﾞｯﾌｧに設定

	_layerGID = MakeScreen(ScreenSize.x, ScreenSize.y, true);

	//_debSetUP(200);

	lpImageMng.GetID("枠", "image/frame.png");
	lpImageMng.GetID("black", "image/black.png");
	lpImageMng.GetID("white", "image/white.png");

	return false;
}
