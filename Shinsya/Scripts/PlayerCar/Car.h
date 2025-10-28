#pragma once

/*
// Carクラスのヘッダー
*/

class Car
{
public:
	Car(P2World& world, const Vec2& pos, double dampingRatio, Array<P2Body> Bodies, const Grid<bool>& blockGrid);
	void draw() const;
	void setMotorSpeed(double speed);
	void jump(double force);
	void stop();
	Vec2 getPosition() const;
	P2Body getBody();

private:
	P2Body body;
	P2Body wheelL;
	P2Body wheelR;
	P2WheelJoint wheelJointL;
	P2WheelJoint wheelJointR;
	HashSet<P2BodyID> groundID;
	const P2BodyID wheelLID;
	const P2BodyID wheelRID;
	P2World& world;
};

