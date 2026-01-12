#pragma once

/*
UI表示を行うヘッダーファイル
*/

class Signboard
{
public:
	Signboard(int in_x, int in_y, float scale);
	// 描画する
	void draw() const;

private:
	Texture texture;
	int pos_x;
	int pos_y;
	float scale;
};

