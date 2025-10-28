#include "stdafx.h"

TitleScene::TitleScene()
	: m_font(40, Typeface::Bold)
	, m_startButton(RectF{ Arg::center = Scene::Center(), 300, 80 }, m_font, U"スタート")
	, m_exitButton(RectF{ Arg::center = Scene::Center().movedBy(0, 100), 300, 80 }, m_font, U"ゲーム終了")
{
}

GameState TitleScene::update()
{
	if (m_startButton.update())
	{
		return GameState::Explain; // ゲーム開始ボタンが押されたらReady状態を返す
	}

	if (m_exitButton.update())
	{
		System::Exit(); // 終了ボタンが押されたらゲームを終了
	}

	return GameState::Title; // 何もなければTitle状態のまま
}

void TitleScene::draw() const
{
	m_startButton.draw();
	m_exitButton.draw();
}
