#include "stdafx.h"
#include "Car.h"

Car::Car(P2World& world, const Vec2& pos, double dampingRatio, const Array<P2Body>& bodies, const Grid<bool>& blockGrid)
	: body(world.createRect(P2Dynamic, pos, SizeF{ 200, 20 }))
	, wheelL(world.createCircle(P2Dynamic, pos + Vec2{ -50, 20 }, 30))
	, wheelR(world.createCircle(P2Dynamic, pos + Vec2{ 50, 20 }, 30))
	, wheelJointL(world.createWheelJoint(body, wheelL, wheelL.getPos(), Vec2{ 0, -1 }))
	, wheelJointR(world.createWheelJoint(body, wheelR, wheelR.getPos(), Vec2{ 0, -1 }))
	, wheelLID(wheelL.id())
	, wheelRID(wheelR.id())
	, world(world)
{
	// 回転の減衰
	wheelL.setAngularDamping(1.5);
	wheelR.setAngularDamping(1.5);

	// グリッド生成処理
	const Size blockSize = { 5, 5 }; // 1ブロックのサイズ
	const double gridTopY = (-20 / 2.0) - (blockGrid.height() * blockSize.y);
	for (auto y : step(blockGrid.height()))
	{
		for (auto x : step(blockGrid.width()))
		{
			if (blockGrid[y][x])
			{
				// 車台の中心からの相対位置を計算
				// グリッドの中心が(0,0)になるように調整
				const Vec2 offset = { (x - blockGrid.width() / 2.0 + 0.5) * blockSize.x,
									  gridTopY + (y + 0.5) * blockSize.y };

				// 車台ボディ(body)に、ブロックを部品として追加
				body.addRect(RectF{ Arg::center = offset, blockSize });
			}
		}
	}

	// ジョイント設定
	wheelJointL.setLinearStiffness(4.0, dampingRatio)
		.setLimits(-5, 5).setLimitsEnabled(true)
		.setMaxMotorTorque(5000).setMotorEnabled(true);
	wheelJointR.setLinearStiffness(4.0, dampingRatio)
		.setLimits(-5, 5).setLimitsEnabled(true)
		.setMaxMotorTorque(5000).setMotorEnabled(true);

	// 地面IDの登録
	for (const auto& groundBody : bodies)
	{
		groundID.insert(groundBody.id());
	}
}

void Car::draw() const
{
	body.draw(Palette::Orange);

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
	// タイヤが地面と接触しているか確認
	bool jumped = false;

	for (auto&& [pair, collision] : world.getCollisions())
	{
		// 衝突している片方が「左タイヤ」または「右タイヤ」か確認
		// かつ、もう片方が「地面IDリスト」に含まれているか確認

		// Aがタイヤ、Bが地面
		if ((pair.a == wheelLID || pair.a == wheelRID) && groundID.contains(pair.b))
		{
			// 対応するタイヤに力を加える
			if (pair.a == wheelLID) wheelL.applyLinearImpulse(Vec2{ 0, -force });
			else                    wheelR.applyLinearImpulse(Vec2{ 0, -force });
			jumped = true;
		}
		// Bがタイヤ、Aが地面
		else if ((pair.b == wheelLID || pair.b == wheelRID) && groundID.contains(pair.a))
		{
			if (pair.b == wheelLID) wheelL.applyLinearImpulse(Vec2{ 0, -force });
			else                    wheelR.applyLinearImpulse(Vec2{ 0, -force });
			jumped = true;
		}
	}

	if (jumped)
	{
		getJumpSound().playOneShot();
	}
}

void Car::stop()
{
	// ボディのタイプを「動的」から「静的」に変更する
	body.setAwake(false);

	// タイヤも同様に止める
	wheelL.setAwake(false);
	wheelR.setAwake(false);
}

Vec2 Car::getPosition() const
{
	return body.getPos();
}

P2Body Car::getBody() const
{
	return body;
}

P2Body Car::getWheelL() const
{
	return wheelL;
}
 
P2Body Car::getWheelR() const
{
	return wheelR;
}

Audio& Car::getJumpSound()
{
	static Audio sound{ U"Assets/Sounds/SE/Jump.mp3" };
	return sound;
}
