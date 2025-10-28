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

	// -----------------------------------
	// 物理ワールドの準備
	// -----------------------------------
	// 重力加速度を設定 (Y軸プラス方向、つまり下向きに 98)
	P2World world{ 98*3 };

	// -----------------------------------
	// 物理オブジェクトの作成
	// -----------------------------------
	// ステージ生成
	Stage stage(world);

	// ゴールの生成
	Goal goal(world);

	// プレイヤーの生成
	Car car(world, Scene::Center(), 0.05, stage.getBodies());

	// タイマーの生成
	DisplayTimer timer;

	// リザルト画面の生成
	Result result;

	// -----------------------------------
	// カメラの作成
	// -----------------------------------
	Camera2D camera{ car.getPosition(), 1.0, CameraControl::None_ };


	// -----------------------------------
	// パラメータ
	// -----------------------------------
	// 新しく追加：速度の最大値を定義
	int32 motorSpeed = 0;

	// ジャンプの強さ
	const double jumpImpulse = 100.0;


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
