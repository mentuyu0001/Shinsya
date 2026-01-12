# include "stdafx.h"
# include <memory>
# include "Scenes/IAppScene/IAppScene.h"
# include "Scripts/Scenes/TitleScene/TitleScene.h"
# include "Scripts/Scenes/PlayingScene/PlayingScene.h"
# include "Scripts/Scenes/ReadyScene/ReadyScene.h"
# include "Scripts/Scenes/ExplainScene/ExplainScene.h"



/// <summary>
/// アプリケーションのエントリーポイント
/// </summary>

void Main()
{
	// 画面を 1280x720 にリサイズする
	Window::Resize(1280, 720);

	// 背景色を設定
	Scene::SetBackground(ColorF{ 0.8, 0.9, 1.0 });

	// BGMの準備
	Audio bgm{ U"Assets/Sounds/BGM/TitleBGM.mp3", Loop::Yes };

	// ゲームステートの準備
	GameState currentState = GameState::Title;
	std::shared_ptr<IAppScene> currentScene = std::make_shared<TitleScene>();

	// ReadySceneからPlayingSceneへ引き継ぐ設計図データ
	// リセット時にも使用するため、Sceneの外で保持する
	Grid<bool> lastDesign(70, 50, false);

	while (System::Update())
	{
		// 1. シーンの更新
		const GameState nextState = currentScene->update();

		// 2. シーンの描画
		currentScene->draw();

		// 3. 状態遷移の処理
		if (nextState != currentState)
		{
			switch (nextState)
			{
			case GameState::Title:
				// タイトル画面
				currentScene = std::make_shared<TitleScene>();
				break;
			case GameState::Explain:
				// 説明画面
				currentScene = std::make_shared<ExplainScene>();
				break;
			case GameState::Ready:
				// 芯車制作画面
				currentScene = std::make_shared<ReadyScene>();
				break;
			case GameState::Playing:
				// Ready -> Playing への遷移時のみ、設計図を更新して保存
				if (auto readyScene = std::dynamic_pointer_cast<ReadyScene>(currentScene))
				{
					bgm.stop();
					lastDesign = readyScene->getGrid(); // 設計図を保存
					currentScene = std::make_shared<PlayingScene>(lastDesign);
				}
				break;
			case GameState::Reset:
				{
					// 保存しておいた設計図(lastDesign)を使って再生成
					// ステートはPlayingに戻す
					currentScene = std::make_shared<PlayingScene>(lastDesign);
					currentState = GameState::Playing;
					continue;
				}
				break;
			case GameState::Ranking:
				// TODO: ランキング実装
				break;

			default:
				throw std::runtime_error("予期せぬゲーム状態への遷移が発生しました");
				break;
			}

			// 現在の状態を更新
			currentState = nextState;
		}

		// タイトル画面のBGM制御
		if (currentState == GameState::Title && !bgm.isPlaying())
		{
			bgm.play();
		}
	}	
}
