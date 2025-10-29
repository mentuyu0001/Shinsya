#pragma once
#include "stdafx.h"
#include "PlayerCar/Car.h"
#include "UI/Timer/DisplayTimer.h"
#include "StageBodies/CreateStage/Stage.h"
#include "UI/Result/Result.h"
#include "StageBodies/Goal/Goal.h"
#include "Scenes/IAppScene/IAppScene.h"

class PlayingScene : public IAppScene
{
public:
	PlayingScene(Grid<bool> myDesign);
	GameState update() override;
	void draw() const override;

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
};
