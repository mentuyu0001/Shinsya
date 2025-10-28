#pragma once

class ReadyScene : public IAppScene
{
public:
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
	Button m_startButton;

	// グリッドの描画設定
	static constexpr Size m_blockSize = { 10, 10 };
	RectF m_gridRect; // グリッド全体の描画領域
};
