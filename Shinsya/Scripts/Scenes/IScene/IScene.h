#pragma once
#include "stdafx.h"
#include "GameState/GameState.h"

/*
// シーンのインターフェース
*/

class IScene
{
public:
	// 仮想デストラクタ
	virtual ~IScene() = default;

	// 純粋仮想関数
	virtual GameState update() = 0;
	virtual void draw() const = 0;
};
