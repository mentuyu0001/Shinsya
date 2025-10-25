#include "stdafx.h"
#include "Goal.h"

/*
// ゴール生成と判定を行うスクリプト
*/

Goal::Goal(P2World& world)
	: goal(world.createRect(P2BodyType::Static, Vec2{ 700, 400 }, SizeF{ 50, 200 })),
	  goalID(goal.id()),
	  world(world)
{

}

void Goal::draw() const
{
	goal.draw(ColorF(1, 0, 0, 0.3));
}

bool Goal::GoalChecker(P2Body player)
{
	P2BodyID playerid = player.id();

	// 衝突時の処理
	for (auto&& [pair, collision] : world.getCollisions())
	{
		if (pair.a == playerid && pair.b == goalID || pair.a == goalID && pair.b == playerid)
		{
			return true;
		}
	}

	return false;
}
