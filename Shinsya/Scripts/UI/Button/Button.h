#pragma once

/*
// ボタン UI クラス
*/

class Button
{
public:
	// コンストラクタ
	Button(const RectF& rect, const Font& font, const String& text);

	// 更新と描画
	bool update();
	void draw() const;

private:
	RectF m_rect;
	Font m_font;
	String m_text;
};

