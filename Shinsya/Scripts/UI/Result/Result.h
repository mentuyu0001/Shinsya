#pragma once
# include "UI/Button/Button.h"

/// <summary>
/// リザルトを表示するクラス
/// </summary>

class Result
{
public:
	/// <summary> リザルトの生成 </summary>
	Result();

	/// <summary> タイトルシーンへの遷移 </summary>
	bool titleUpdate();

	/// <summary> やり直し処理 </summary>
	bool resetUpdate();

	/// <summary> リザルトの描画 </summary>
	void draw() const;

	/// <summary> ゴール時の処理 </summary>
	void Goal(float clearTime);

private:
	bool isGoal;
	double time;
	const Font font;
	Button returnTitleButton;
	Button resetButton;
};

