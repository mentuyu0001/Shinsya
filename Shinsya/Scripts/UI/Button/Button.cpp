#include "stdafx.h"

/*
// ボタンUIスクリプト
*/

Button::Button(const RectF& rect, const Font& font, const String& text)
	: m_rect(rect)
	, m_font(font)
	, m_text(text)
{
}

bool Button::update()
{
	if (m_rect.mouseOver())
	{
		// カーソルを手の形にする
		Cursor::RequestStyle(CursorStyle::Hand);
	}


	// ボタンが左クリックされたフレームなら true を返す
	return m_rect.leftClicked();
}

void Button::draw() const
{
	if (m_rect.mouseOver())
	{
		// 少し暗い色で背景を描画
		m_rect.rounded(6).draw(ColorF{ 0.9, 0.9, 0.9 });
	}
	else
	{
		// 通常の色で背景を描画
		m_rect.rounded(6).draw(ColorF{ 1.0 });
	}

	// テキストを描画
	m_font(m_text).drawAt(m_rect.center(), ColorF{ 0.1 });
}
