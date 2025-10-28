# include "stdafx.h"
#include <memory>
# include "Scenes/IAppScene/IAppScene.h"
# include "Scripts/Scenes/TitleScene/TitleScene.h"
# include "Scripts/Scenes/PlayingScene/PlayingScene.h"



/*
// メインスクリプト
*/

void Main()
{
	// --- テスト用のブロック配置データを作成 ---
	Grid<bool> myDesign(70, 50, false);
	//myDesign[24][25] = false;
	//myDesign[25][25] = false;
	//myDesign[26][25] = false;

	// 画面を 1280x720 にリサイズする
	Window::Resize(1280, 720);

	// 背景色を設定
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// -----------------------------------
	// ゲームステートの準備
	// -----------------------------------
	GameState currentState = GameState::Title;
	std::shared_ptr<IAppScene> currentScene = std::make_shared<TitleScene>();

	// -----------------------------------
	// 各シーンのオブジェクトを作成
	// -----------------------------------
	TitleScene titleScene;
	PlayingScene playingScene(myDesign);

	while (System::Update())
	{
		const GameState nextState = currentScene->update();

		// 2. 現在のシーンの描画処理を呼ぶ
		currentScene->draw();

		// -----------------------------------
		// ゲームステートごとの処理
		// -----------------------------------
		if (nextState != currentState)
		{
			switch (nextState)
			{
			case GameState::Title:
				// タイトル画面
				currentScene = std::make_shared<TitleScene>();
				break;
			case GameState::Ready:
				// 芯車制作画面
				break;
			case GameState::Playing:
				currentScene = std::make_shared<PlayingScene>(myDesign);
				break;

			case GameState::Rnaking:
				// ランキング表示

				break;

			default:
				// 予期せぬ状態遷移
				throw std::runtime_error("ゲームが予期せない遷移をしました");
				break;
			}

			// 現在の状態を更新
			currentState = nextState;
		}
	}	
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
