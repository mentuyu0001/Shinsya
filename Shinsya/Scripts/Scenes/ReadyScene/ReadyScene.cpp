#include "stdafx.h"
#include "ReadyScene.h"

ReadyScene::ReadyScene()
// メンバー変数を初期化
	: m_blockGrid(70, 50, false)
	, m_font(48, Typeface::Bold)
	// スタートボタンはグリッドの下に配置
	, m_startButton(RectF{ Arg::center = Scene::Center().movedBy(0, 300), 300, 80 }, m_font, U"これで開始！")
{
	// グリッド全体のサイズを計算
	const Size totalGridSize = (m_blockGrid.size() * m_blockSize);
	// 画面中央に配置されるように描画領域を設定
	m_gridRect = RectF{ Arg::center = Scene::Center(), totalGridSize };
}

GameState ReadyScene::update()
{
	// スタートボタンが押されたら、Playing状態に移行する
	if (m_startButton.update())
	{
		return GameState::Playing;
	}

	// マウスカーソルがグリッド領域の上にある場合のみ処理
	if (m_gridRect.mouseOver())
	{
		// スクリーン座標をグリッド座標に変換
		const auto gridPos = (Cursor::PosF() - m_gridRect.pos) / m_blockSize;
		const int32 x = static_cast<int32>(gridPos.x);
		const int32 y = static_cast<int32>(gridPos.y);

		// マウスが左クリックされたら、そのマスの状態を反転させる
		if (MouseL.pressed())
		{
			// グリッドの範囲内かチェック
			if ((0 <= y && y < m_blockGrid.height()) && (0 <= x && x < m_blockGrid.width()))
			{
				m_blockGrid[y][x] = !m_blockGrid[y][x];
			}
		}
	}

	// 何もなければReady状態のまま
	return GameState::Ready;
}

void ReadyScene::draw() const
{
	// グリッドの背景を少し暗く描画
	m_gridRect.draw(ColorF{ 0.2, 0.2, 0.2 });

	// グリッドの状態を描画
	for (auto y : step(m_blockGrid.height()))
	{
		for (auto x : step(m_blockGrid.width()))
		{
			// 各マスの描画位置を計算
			const RectF cellRect{ m_gridRect.pos + (Point{ x, y } *m_blockSize), m_blockSize };

			// ブロックが置かれていたら、色を付けて描画
			if (m_blockGrid[y][x])
			{
				cellRect.draw(Palette::Orange);
			}

			// マス目の枠線を描画
			cellRect.drawFrame(1, ColorF{ 0.5 });
		}
	}

	m_startButton.draw();
}

// 完成したグリッドを返すゲッター関数
const Grid<bool>& ReadyScene::getGrid() const
{
	return m_blockGrid;
}
