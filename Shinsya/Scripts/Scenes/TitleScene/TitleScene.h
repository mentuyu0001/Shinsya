#pragma once
#include "stdafx.h"
#include "Scenes/IAppScene/IAppScene.h"
#include "UI/Button/Button.h"

class TitleScene : public IAppScene
{
public:
	TitleScene();
	GameState update() override;
	void draw() const override;

private:
	Font m_font;
	Button m_startButton;
	Button m_exitButton;
};
