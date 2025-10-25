#include "stdafx.h"
#include "Car.h"

/*
// Carクラス
*/

Car::Car(P2World& world, const Vec2& pos, double dampingRatio, Array<P2Body> Bodies)
	: body(world.createRect(P2Dynamic, pos, SizeF{ 200, 40 }))
	, wheelL(world.createCircle(P2Dynamic, pos + Vec2{ -50, 20 }, 30))
	, wheelR(world.createCircle(P2Dynamic, pos + Vec2{ 50, 20 }, 30))
	, wheelJointL(world.createWheelJoint(body, wheelL, wheelL.getPos(), Vec2{ 0, -1 }))
	, wheelJointR(world.createWheelJoint(body, wheelR, wheelR.getPos(), Vec2{ 0, -1 }))
	, wheelLID(wheelL.id())
	, wheelRID(wheelR.id())
	, world(world)
{
	wheelL.setAngularDamping(1.5); // 回転の減衰
	wheelR.setAngularDamping(1.5); // 回転の減衰

	wheelJointL.setLinearStiffness(4.0, dampingRatio)
		.setLimits(-5, 5).setLimitsEnabled(true)
		.setMaxMotorTorque(1000).setMotorEnabled(true);
	wheelJointR.setLinearStiffness(4.0, dampingRatio)
		.setLimits(-5, 5).setLimitsEnabled(true)
		.setMaxMotorTorque(1000).setMotorEnabled(true);

	for (const auto& body : Bodies)
	{
		groundID.insert(body.id());
	}
}

void Car::draw() const
{
	body.draw();
	wheelL.draw(ColorF{ 0.25 }).drawWireframe(2, Palette::Orange);
	wheelR.draw(ColorF{ 0.25 }).drawWireframe(2, Palette::Orange);
}

void Car::setMotorSpeed(double speed)
{
	wheelJointL.setMotorSpeed(speed);
	wheelJointR.setMotorSpeed(speed);
}

void Car::jump(double force)
{
	// 地面と接地してるときのみジャンプが行える
	for (auto&& [pair, collision] : world.getCollisions())
	{
		for (const auto& groundid : groundID)
		{
			// 衝突のうち片方が地面の ID であれば、もう片方が地面と接触しているボディ
			if (pair.a == groundid && pair.b == wheelLID || pair.a == wheelLID && pair.b == groundid)
			{
				wheelL.applyLinearImpulse(Vec2{ 0, -force });
			}

			if (pair.a == groundid && pair.b == wheelRID || pair.a == wheelRID && pair.b == groundid)
			{
				wheelR.applyLinearImpulse(Vec2{ 0, -force });
			}
		}
	}
}

P2Body Car::getBody()
{
	return body;
}
