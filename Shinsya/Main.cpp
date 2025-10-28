# include "stdafx.h"


/*
// メインスクリプト
*/

void Main()
{
	// 画面を 1280x720 にリサイズする
	Window::Resize(1280, 720);

	// 背景色を設定
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// -----------------------------------
	// ゲームステートの準備
	// -----------------------------------
	GameState gameState = GameState::Title;

	// -----------------------------------
	// 各シーンのオブジェクトを作成
	// -----------------------------------
	TitleScene titleScene;
	PlayingScene playingScene;

	while (System::Update())
	{
		// -----------------------------------
		// ゲームステートごとの処理
		// -----------------------------------
		switch (gameState)
		{
		case GameState::Title:
			// タイトル画面
			titleScene.draw();
			gameState = titleScene.update();
			break;
		case GameState::Ready:
			// 芯車制作画面
			break;
		case GameState::Playing:
			playingScene.draw();
			gameState = playingScene.update();
			break;

		case GameState::Rnaking:
			// ランキング表示

			break;

		default:
			// 予期せぬ状態遷移
			throw std::runtime_error("ゲームが予期せない遷移をしました");
			break;
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
