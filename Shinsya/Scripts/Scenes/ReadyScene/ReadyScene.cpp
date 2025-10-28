#include "stdafx.h"
#include "ReadyScene.h"

/*
// 芯車制作画面のシーンクラス
*/

ReadyScene::ReadyScene()
// メンバー変数を初期化
	: m_blockGrid(70, 50, false)
	, m_coreGrid(70, 50, false)
	, m_font(40, Typeface::Bold)
	, m_currentMode(EditMode::Pen)
	, m_penButton(RectF{ Arg::center = Scene::Center().movedBy(500, -200), 250, 80 }, m_font, U"ペン")
	, m_eraserButton(RectF{ Arg::center = Scene::Center().movedBy(500, -100), 250, 80 }, m_font, U"消しゴム")
	, m_startButton(RectF{ Arg::center = Scene::Center().movedBy(0, 270), 300, 80 }, m_font, U"これで開始！")
	, m_elapsedTime(0.0)
	, m_previewCenter(Scene::Center().movedBy(500, 250))
{
	// グリッド全体のサイズを計算
	const Size totalGridSize = (m_blockGrid.size() * m_blockSize);
	// 画面中央に配置されるように描画領域を設定
	m_gridRect = RectF{ Arg::center = Scene::Center().movedBy(0, -50), totalGridSize };


	// プレビュー用の図形を初期化
	const SizeF carBodySize = { 200, 40 };
	m_previewBody = RectF{ Arg::center = m_previewCenter, carBodySize * m_previewScale };
	m_previewWheelL = Circle{ m_previewCenter + Vec2{ -50, 20 } *m_previewScale, 30 * m_previewScale };
	m_previewWheelR = Circle{ m_previewCenter + Vec2{ 50, 20 } *m_previewScale, 30 * m_previewScale };

	const int32 centerX = m_blockGrid.width() / 2; // グリッドのX方向中心 (35)
	const int32 crossbarWidth = 12; // 横棒の幅 (偶数にすると綺麗)
	
	// 横棒を配置
	for (int32 x = centerX - (crossbarWidth / 2); x < centerX + (crossbarWidth / 2); ++x)
	{
		// グリッドの一番上の行 (y=0) に横棒を置く
		if (m_blockGrid.inBounds(0, x))
		{
			m_blockGrid[0][x] = true;
			m_coreGrid[0][x] = true; // ここは「芯」であると記憶
		}
	}

	// 縦棒を配置
	for (int32 y = 0; y < m_blockGrid.height(); ++y)
	{
		// 中心2マスを縦棒として使う
		if (m_blockGrid.inBounds(y, centerX - 1))
		{
			m_blockGrid[y][centerX - 1] = true;
			m_coreGrid[y][centerX - 1] = true; // ここは「芯」であると記憶
		}
		if (m_blockGrid.inBounds(y, centerX))
		{
			m_blockGrid[y][centerX] = true;
			m_coreGrid[y][centerX] = true; // ここは「芯」であると記憶
		}
	}
}

GameState ReadyScene::update()
{
	if (m_startButton.update()) { return GameState::Playing; }

	// モード切替ボタンの処理
	if (m_penButton.update()) { m_currentMode = EditMode::Pen; }
	if (m_eraserButton.update()) { m_currentMode = EditMode::Eraser; }

	// マウスカーソルがグリッド領域の上にある場合のみ処理
	m_elapsedTime += Scene::DeltaTime();
	if (m_elapsedTime >= 0.2)
	{
		if (m_gridRect.mouseOver())
		{
			// スクリーン座標をグリッド座標に変換
			const auto gridPos = (Cursor::PosF() - m_gridRect.pos) / m_blockSize;
			const int32 x = static_cast<int32>(gridPos.x);
			const int32 y = static_cast<int32>(gridPos.y);

			// マウスが左クリックされたら、そのマスの状態を反転させる
			if (MouseL.pressed())
			{
				if (m_currentMode == EditMode::Pen)
				{
					m_blockGrid[y][x] = true; // ペンモードならブロックを置く
				}
				else if (m_currentMode == EditMode::Eraser)
				{
					if (not m_coreGrid[y][x])
					{
						m_blockGrid[y][x] = false;
					}
				}
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
				if (m_coreGrid[y][x])
				{
					cellRect.draw(ColorF{ 0.7 }); // 「芯」の色 (例: グレー)
				}
				else
				{
					cellRect.draw(Palette::Orange); // プレイヤーが置いたブロックの色
				}
			}

			// マス目の枠線を描画
			cellRect.drawFrame(1, ColorF{ 0.5 });
		}
	}

	m_penButton.draw(m_currentMode == EditMode::Pen);
	m_eraserButton.draw(m_currentMode == EditMode::Eraser);
	m_startButton.draw();

	{
		// プレビュー描画用の座標系を作成
		const Transformer2D t{ Mat3x2::Translate(m_previewCenter) };

		// プレビュー用の車台とタイヤを描画
		m_previewBody.movedBy(-m_previewCenter).draw(Palette::Orange);
		m_previewWheelL.movedBy(-m_previewCenter).draw(ColorF{ 0.25 });
		m_previewWheelR.movedBy(-m_previewCenter).draw(ColorF{ 0.25 });

		// グリッドのブロックを、縮小してプレビュー車台の上に描画
		const SizeF carBodySize = { 200, 40 };
		const double gridTopY = (-40 / 2.0) - (m_blockGrid.height() * m_blockSize.y);

		for (auto y : step(m_blockGrid.height()))
		{
			for (auto x : step(m_blockGrid.width()))
			{
				if (m_blockGrid[y][x])
				{
					// ブロックの相対位置を計算
					const Vec2 offset = {
						(x - m_blockGrid.width() / 2.0 + 0.5) * m_blockSize.x,
						gridTopY + (y + 0.5) * m_blockSize.y
					};

					// 縮小して描画
					RectF{ Arg::center = (offset * m_previewScale), m_blockSize * m_previewScale }.draw(Palette::Orange);
				}
			}
		}
	}
}

// 完成したグリッドを返すゲッター関数
const Grid<bool>& ReadyScene::getGrid() const
{
	return m_blockGrid;
}
