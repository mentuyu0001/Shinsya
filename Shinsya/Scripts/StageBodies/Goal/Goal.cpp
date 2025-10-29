#include "stdafx.h"
#include "Goal.h"

/*
// ゴール生成と判定を行うスクリプト
*/

Goal::Goal(P2World& world)
	: goal(world.createRect(P2BodyType::Static, Vec2{ 3170, 77 }, SizeF{ 100, 1000 })),
	  goalID(goal.id()),
	  world(world)
{

}

void Goal::draw() const
{
	goal.draw(ColorF(1, 0, 0, 0.5));
}

bool Goal::GoalChecker(P2Body player)
{
	P2BodyID playerid = player.id();

	// 衝突時の処理
	for (auto&& [pair, collision] : world.getCollisions())
	{
		if (pair.a == playerid && pair.b == goalID || pair.a == goalID && pair.b == playerid)
		{
			if (!m_isReached)
			{
				getGoalSound().playOneShot();

				m_isReached = true;
			}
			return true;
		}
	}

	return false;
}

Audio& Goal::getGoalSound()
{
	static Audio sound{ U"Assets/Sounds/SE/Goal.mp3" };
	return sound;
}
