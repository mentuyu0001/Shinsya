#pragma once

/// <summary>
/// ボタン UI クラス
/// </summary>

class Button
{
public:
	/// <summary> ボタンの生成 </summary>
	Button(const RectF& rect, const Font& font, const String& text);

	/// <summary> ボタンのアニメーション処理とアクション処理 </summary>
	bool update();

	/// <summary> ボタンの描画 </summary>
	void draw(bool isActive = false) const;

private:
	RectF m_rect;
	Font m_font;
	String m_text;
	bool m_wasHovered = false;
	static Audio& getSelectSound();
	static Audio& getClickSound();
};

