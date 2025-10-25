#pragma once
#include <Siv3D.hpp> // Siv3Dの機能を使うので必須

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
