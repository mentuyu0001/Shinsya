#pragma once

/// <summary>
/// プレイヤーが操作する車のクラス
/// </summary>

class Car
{
public:
	/// <summary> 車オブジェクトの生成 </summary>
	Car(P2World& world, const Vec2& pos, double dampingRatio, const Array<P2Body>& bodies, const Grid<bool>& blockGrid);

	/// <summary> 車とタイヤの描画 </summary>
	void draw() const;

	/// <summary> 車輪のスピードセット </summary>
	void setMotorSpeed(double speed);

	/// <summary> 接地してる間だけジャンプする </summary>
	void jump(double force);

	/// <summary> 物理演算を停止 </summary>
	void stop();

	/// <summary> 車の位置を取得 </summary>
	Vec2 getPosition() const;

	/// <summary> 各Bodyの取得 </summary>
	P2Body getBody() const;
	P2Body getWheelL() const;
	P2Body getWheelR() const;

private:
	P2World& world;
	P2Body body;
	P2Body wheelL;
	P2Body wheelR;
	P2WheelJoint wheelJointL;
	P2WheelJoint wheelJointR;

	// 地面のBodyIDを高速に検索するためのハッシュセット
	HashSet<P2BodyID> groundID;

	const P2BodyID wheelLID;
	const P2BodyID wheelRID;

	static Audio& getJumpSound();
};

