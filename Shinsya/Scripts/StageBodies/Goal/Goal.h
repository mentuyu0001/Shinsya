#pragma once

/*
// ゴール生成と判定を行うヘッダー
*/

class Goal
{
public:
	Goal(P2World& world);

	void draw() const;

	// ゴール判定
	bool GoalChecker(P2Body player);

private:
	bool m_isReached = false;
	P2Body goal;
	P2BodyID goalID;
	P2World& world;
	static Audio& getGoalSound();
};

