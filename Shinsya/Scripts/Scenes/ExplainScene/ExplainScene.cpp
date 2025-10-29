#include "stdafx.h"
#include "ExplainScene.h"

/*
 // 説明画面のシーンクラス
 */

ExplainScene::ExplainScene()
	: m_font_text(28, Typeface::Bold)
	, m_font_button(40, Typeface::Bold)
	, m_startButton(RectF{ Arg::center = Scene::Center().movedBy(0, 250), 300, 80 }, m_font_button, U"芯車を作る")
	, texture(U"Assets/Images/Title/Title.png")
{
}

GameState ExplainScene::update()
{
	if (m_startButton.update())
	{
		return GameState::Ready; // スタートボタンが押されたらReady状態を返す
	}
	return GameState::Explain; // 何もなければExplain状態のまま
}

void ExplainScene::draw() const
{
	texture.draw(0, 0);

	// 説明文の描画
	const String explanationText =
		U"ようこそ！芯車 -シンシャ- へ！\n\n"
		U"このゲームでは自分だけの芯車をデザインして、\n"
		U"レースに挑戦してもらいます。\n\n"
		U"まずは「芯車を作る」ボタンを押して、\n"
		U"芯車制作画面に進んでください。\n\n"
		U"マス目にブロックを配置して、\n"
		U"あなただけのオリジナル芯車を作りましょう！\n\n"
		U"最高の芯車で最速を目指してください！";
	const RectF textRegion = m_font_text(explanationText).region(Arg::center = Scene::Center().movedBy(0, -80));
	const RoundRect backgroundRect = textRegion.stretched(20).rounded(10);

	backgroundRect.draw(ColorF{ 1.0, 0.9 }); // 少しだけ透明な白

	m_font_text(explanationText).drawAt(Scene::Center().movedBy(0, -80), Palette::Black);

	m_startButton.draw();
}
