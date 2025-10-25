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
	P2Body goal;
	P2BodyID goalID;
	P2World& world;
};

