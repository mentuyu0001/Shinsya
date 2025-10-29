#include "stdafx.h"
#include "Stage.h"

/*
// ステージ制作を行うスクリプト
*/

Stage::Stage(P2World& world)
	: m_texture((U"Assets/Images/Stage/Stage.png"))
{
	const Image stageImage{ U"Assets/Images/Stage/Stage.png" };
	const MultiPolygon stagePolygons = stageImage.alphaToPolygons(128, AllowHoles::Yes).simplified(4.0);
	m_staticBodies.push_back(world.createPolygons(P2BodyType::Static, Vec2{ -400, -1000 }, stagePolygons));
}

void Stage::draw() const
{
	// 保持している全てのボディをループで描画する
	for (const auto& body : m_staticBodies)
	{
		body.draw();
	}
	m_texture.draw(-400, -1000);
}

const Array<P2Body>& Stage::getBodies() const
{
	return m_staticBodies;
}
