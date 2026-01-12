#pragma once

/// <summary>
/// ステージ制作を行うクラス
/// </summary>

class Stage
{
public:
	/// <summary> ステージの生成 </summary>
	Stage(P2World& world);

	/// <summary> ステージの全要素を描画する </summary>
	void draw() const;

	/// <summary> ステージの静的物体群を取得する </summary>
	const Array<P2Body>& getBodies() const;

private:
	Texture m_texture;
	Array<P2Body> m_staticBodies;
};
