#include "stdafx.h"
#include "PlayingScene.h"


// コンストラクタで、Mainにあったオブジェクトをすべて初期化する
PlayingScene::PlayingScene(Grid<bool> myDesign)
	: texture(U"Assets/Images/Stage/Background.png")
	, m_world(98 * 3)
	, m_stage(m_world)
	, m_goal(m_world)
	, font({ FontMethod::MSDF, 48, Typeface::Bold })
	, m_car(m_world, Scene::Center(), 0.05, m_stage.getBodies(), myDesign)
	, m_timer()
	, m_result()
	, m_camera(m_car.getPosition(), 1.0, CameraControl::None_)
{
}

GameState PlayingScene::update()
{
	m_world.update();
	m_camera.setTargetCenter(m_car.getPosition());
	m_camera.update();

	m_car.setMotorSpeed(m_motorSpeed);
	m_timer.addTime();

	if (MouseL.pressed() || KeyLeft.pressed()) { m_motorSpeed = -500; }
	else if (MouseR.pressed() || KeyRight.pressed()) { m_motorSpeed = 500; }
	else { m_motorSpeed = 0; }

	if (KeySpace.down()) { m_car.jump(m_jumpImpulse); }

	if (m_goal.GoalChecker(m_car.getBody()) || m_goal.GoalChecker(m_car.getWheelL()) || m_goal.GoalChecker(m_car.getWheelR()))
	{
		m_timer.Goal();
		m_result.Goal(m_timer.getTime());
		m_car.stop();
	}

	// リザルト画面で「タイトルに戻る」が押されたらTitle状態を返す
	if (m_result.titleUpdate())
	{
		return GameState::Title;
	}
	// リザルト画面で「リトライ」が押されたらReset状態を返す
	else if (m_result.resetUpdate())
	{
		return GameState::Reset;
	}

	if (KeyR.down())
	{
		// Rキーが押されたら、Reset状態を返す
		return GameState::Reset;
	}

	return GameState::Playing; // 何もなければPlaying状態のまま
}

void PlayingScene::draw() const
{
	{
		texture.draw(0, 0);
	}
	{
		const auto t = m_camera.createTransformer();
		m_stage.draw();
		m_goal.draw();
		m_car.draw();
	}
	{
		const String resetText = U"Rキー：リセット";
		font(resetText).draw(40, Vec2{ 40, 100 }, Palette::Black);
		m_timer.draw();
		m_result.draw();
	}
}
