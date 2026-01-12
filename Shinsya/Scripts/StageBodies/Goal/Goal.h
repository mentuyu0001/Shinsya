#pragma once

/// <summary>
/// ゴール生成と判定を行うヘッダー
///  </summary>

class Goal
{
public:
	/// <summary> ゴールの生成 </summary>
	Goal(P2World& world);

	/// <summary> ゴールの描画 </summary>
	void draw() const;

	/// <summary> ゴール判定 </summary>
	bool GoalChecker(P2Body player);

private:
	bool m_isReached = false;
	P2Body goal;
	P2BodyID goalID;
	P2World& world;
	static Audio& getGoalSound();
};

