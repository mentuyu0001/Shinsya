#pragma once

/*
// 芯車制作画面のシーンクラス
*/

class ReadyScene : public IAppScene
{
public:
	// 編集モードのenumを定義
	enum class EditMode
	{
		Pen,
		Eraser,
		None
	};

	ReadyScene();
	GameState update() override;
	void draw() const override;

	// 完成したグリッドのデータを外部に渡すための関数
	const Grid<bool>& getGrid() const;

private:
	// グリッドのデータ本体 (70x50)
	Grid<bool> m_blockGrid;

	// UI部品
	Font m_font;

	// 編集モード関連
	EditMode m_currentMode; // 現在の編集モード
	Button m_penButton;     // ペンモードボタン
	Button m_eraserButton;  // 消しゴムモードボタン
	Button m_startButton;   // 開始ボタン

	// グリッドの描画設定
	static constexpr Size m_blockSize = { 10, 10 };
	RectF m_gridRect; // グリッド全体の描画領域

	double m_elapsedTime;

	// プレビュー表示用のメンバー変数を追加
	Vec2 m_previewCenter;    // プレビュー全体の中心座標
	RectF m_previewBody;      // プレビュー用の車台
	Circle m_previewWheelL;    // プレビュー用の左タイヤ
	Circle m_previewWheelR;    // プレビュー用の右タイヤ
	static constexpr double m_previewScale = 0.3; // プレビューの縮尺
};
