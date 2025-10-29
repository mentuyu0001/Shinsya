#include "stdafx.h"
#include "Stage.h"

/*
// ステージ制作を行うスクリプト
*/

Stage::Stage(P2World& world)
{
	// 作成したボディを、m_staticBodies配列にどんどん追加していく
	m_staticBodies.push_back(world.createRect(P2BodyType::Static, Vec2{ 640, 500 }, SizeF{ 1000, 10 }));
}

void Stage::draw() const
{
	// 保持している全てのボディをループで描画する
	for (const auto& body : m_staticBodies)
	{
		body.draw(Palette::Seagreen);
	}
}

const Array<P2Body>& Stage::getBodies() const
{
	return m_staticBodies;
}
