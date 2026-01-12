#pragma once
#include "stdafx.h"
#include "Scenes/IAppScene/IAppScene.h"
#include "UI/Button/Button.h"

/// <summary>
/// タイトルシーンのクラス
/// </summary>


class TitleScene : public IAppScene
{
public:
	/// <summary> タイトルシーンの生成 </summary>
	TitleScene();

	/// <summary> 次シーンへの遷移 </summary>
	GameState update() override;

	/// <summary> タイトルシーン全体の描画 </summary>
	void draw() const override;

private:
	Font m_font;
	Button m_startButton;
	Button m_exitButton;
	const Texture texture;
};
