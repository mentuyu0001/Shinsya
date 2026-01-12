#pragma once

/// <summary>
/// 操作説明を行うクラス
/// </summary>

class Signboard
{
public:
	/// <summary> 操作説明UIの生成 </summary>
	Signboard(int in_x, int in_y, float scale);

	/// <summary> 操作説明UIの描画 </summary>
	void draw() const;

private:
	Texture texture;
	int pos_x;
	int pos_y;
	float scale;
};

