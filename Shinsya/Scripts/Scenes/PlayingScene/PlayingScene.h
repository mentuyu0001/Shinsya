#pragma once
#include "stdafx.h"
#include "GameState/GameState.h"
#include "PlayerCar/Car.h"
#include "StageBodies/CreateStage/Stage.h"

class PlayingScene
{
public:
	PlayingScene();
	GameState update();
	void draw() const;

private:
	P2World m_world;
	Stage m_stage;
	Goal m_goal;
	Car m_car;
	DisplayTimer m_timer;
	Result m_result;
	Camera2D m_camera;
	int32 m_motorSpeed = 0;
	const double m_jumpImpulse = 100.0;
};
