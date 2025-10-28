# include <Siv3D.hpp> // Siv3D v0.6.16
#include <memory>

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
			gameState = titleScene.update();
			titleScene.draw();
			break;
		case GameState::Ready:
			// 芯車制作画面
			break;
		case GameState::Playing:
			// プレイ中
			
			// -----------------------------------
			// 物理ワールドの更新
			// -----------------------------------
			// 1フレーム分のシミュレーションを進める
			world.update();
			// カメラの更新
			camera.setTargetCenter(car.getPosition());
			camera.update();
			// -----------------------------------
			// 車の更新
			// -----------------------------------
			// 車を動かす
			car.setMotorSpeed(motorSpeed);

			// -----------------------------------
			// タイマーの更新
			// -----------------------------------
			// 時間を加算する
			timer.addTime();

			// -----------------------------------
			// 入力に応じて力を加える
			// -----------------------------------
			// 左クリックされたら、左方向に力を加える
			if (MouseL.pressed() || KeyLeft.pressed())
			{
				motorSpeed = -500;
			}

			// 右クリックされたら、右方向に力を加える
			if (MouseR.pressed() || KeyRight.pressed())
			{
				motorSpeed = 500;
			}

			// 何も押されてない間はmotorSpeedを0にする
			if (!MouseR.pressed() && !KeyRight.pressed() && !MouseL.pressed() && !KeyLeft.pressed())
			{
				motorSpeed = 0;
			}

			//------------------------------------
			// ジャンプ処理
			//------------------------------------
			// スペースキーが押された
			if (KeySpace.down())
			{
				car.jump(jumpImpulse);
			}

			//------------------------------------
			// ゴール判定
			//------------------------------------
			if (goal.GoalChecker(car.getBody()))
			{
				timer.Goal();
				result.Goal(timer.getTime());
				car.stop();
			}


			// -----------------------------------
			// 描画
			// -----------------------------------
			// カメラと一緒に動く物の描画
			{
				// カメラの座標変換
				const auto t = camera.createTransformer();
				// ステージの描画
				stage.draw();
				// ゴールの描画
				goal.draw();
				// プレイヤーの描画
				car.draw();
			}
			// カメラに関係なく固定な物の描画
			{
				// タイマーの描画
				timer.draw();
				if (result.update())
				{
					// タイトルに戻るボタンが押された
					gameState = GameState::Title;
				}
			}
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
