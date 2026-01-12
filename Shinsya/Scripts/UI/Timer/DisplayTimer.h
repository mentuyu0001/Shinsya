#pragma once

/// <summary>
/// タイマーを表示するヘッダー
/// </summary>

class DisplayTimer
{
public:
	/// <summary> タイマーの生成 </summary>
	DisplayTimer();

	/// <summary> タイマーの描画 </summary>
	void draw() const;

	/// <summary> ゴール時の処理 </summary>
	void Goal();

	/// <summary> ゴールしたかどうかを取得 </summary>
	bool getIsGoal() const;

	/// <summary> タイマーの時間を加算 </summary>
	void addTime();

	/// <summary> タイマーの時間を取得 </summary>
	float getTime() const;

private:
	bool isGoal;
	double time;
	const Font font;
};

