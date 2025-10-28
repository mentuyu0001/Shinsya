#pragma once
#include "stdafx.h"
#include "Scenes/IAppScene/IAppScene.h"
#include "UI/Button/Button.h"

/*
// 説明画面のシーンクラス
*/
class ExplainScene : public IAppScene
{
public:
	ExplainScene();
	GameState update() override;
	void draw() const override;

private:
	Font m_font_text;
	Font m_font_button;
	Button m_startButton;
};
