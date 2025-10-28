#pragma once
#include "stdafx.h"
#include "GameState/GameState.h"
#include "PlayerCar/Car.h"
#include "StageBodies/CreateStage/Stage.h"
#include "Scenes/IAppScene/IAppScene.h" // 既存の include の下に追加

class PlayingScene : public IAppScene
{
public:
	PlayingScene(Grid<bool> myDesign);
	GameState update() override;
	void draw() const override;

private:
	P2World m_world;
	Stage m_stage;
	Goal m_goal;
	Car m_car;
	DisplayTimer m_timer;
	Result m_result;
	Camera2D m_camera;
	int32 m_motorSpeed = 0;
	const double m_jumpImpulse = 300.0;
};
