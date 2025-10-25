#pragma once

/*
ステージ制作を行うヘッダーファイル
*/
class Stage
{
public:
	Stage(P2World& world);

	// ステージの全要素を描画する
	void draw() const;

	const Array<P2Body>& getBodies() const;

private:
	Array<P2Body> m_staticBodies;
};
