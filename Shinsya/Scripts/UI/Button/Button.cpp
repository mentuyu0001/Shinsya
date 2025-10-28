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

void Button::draw(bool isActive) const
{
	const RoundRect roundRect = m_rect.rounded(6);
	roundRect.drawShadow(Vec2{ 2, 2 }, 12, 0);

	if (isActive)
	{
		m_rect.rounded(6).draw(ColorF{ 0.6, 0.8, 1.0 }); // アクティブ時の色 (例: 明るい青)
	}
	else if (m_rect.mouseOver())
	{
		// 少し暗い色で背景を描画
		m_rect.rounded(6).draw(ColorF{ 0.9, 0.9, 0.9 });
	}
	else
	{
		// 通常の色で背景を描画
		m_rect.rounded(6).draw(ColorF{ 1.0 });
	}

	m_rect.stretched(-3).rounded(3).drawFrame(2, ColorF{ 0.4, 0.3, 0.2 });

	// テキストを描画
	m_font(m_text).drawAt(m_rect.center(), ColorF{ 0.1 });
}
