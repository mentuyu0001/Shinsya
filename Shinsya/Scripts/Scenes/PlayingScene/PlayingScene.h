#pragma once
#include "stdafx.h"
#include "PlayerCar/Car.h"
#include "UI/Timer/DisplayTimer.h"
#include "StageBodies/CreateStage/Stage.h"
#include "UI/Result/Result.h"
#include "StageBodies/Goal/Goal.h"
#include "Scenes/IAppScene/IAppScene.h"
#include "StageBodies/Signboard/Signboard.h"

/// <summary>
/// プレイシーンのクラス
/// </summary>

class PlayingScene : public IAppScene
{
public:
	/// <summary> プレイシーンの生成 </summary>
	PlayingScene(Grid<bool> myDesign);

	/// <summary> 次画面への遷移 </summary>
	GameState update() override;

	/// <summary> プレイシーン全体の描画 </summary>
	void draw() const override;
	static void StartBGM();
	static void StopBGM();

private:
	const Texture texture;
	P2World m_world;
	Stage m_stage;
	Goal m_goal;
	Car m_car;
	DisplayTimer m_timer;
	Font font;
	Result m_result;
	Camera2D m_camera;
	int32 m_motorSpeed = 0;
	const double m_jumpImpulse = 300.0;
	static Audio& GetBGM();
	Signboard m_signboard;
};
