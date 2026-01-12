#pragma once
#include "stdafx.h"
#include "Scenes/IAppScene/IAppScene.h"
#include "UI/Button/Button.h"

/// <summary>
/// 説明画面のシーンクラス
/// </summary>

class ExplainScene : public IAppScene
{
public:
	/// <summary> 説明シーンの生成 </summary>
	ExplainScene();

	/// <summary> 次画面への遷移 </summary>
	GameState update() override;

	/// <summary> 説明シーン全体の描画 </summary>
	void draw() const override;

private:
	Font m_font_text;
	Font m_font_button;
	Button m_startButton;
	const Texture texture;
};
