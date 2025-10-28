#pragma once
#include "stdafx.h"
#include "Scenes/IScene/IScene.h"
#include "UI/Button/Button.h"

class TitleScene
{
public:
	TitleScene();
	GameState update();
	void draw() const;

private:
	Font m_font;
	Button m_startButton;
	Button m_exitButton;
};
