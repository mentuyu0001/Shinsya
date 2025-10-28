#pragma once

/*
// ゲームの状態を定義する列挙型
*/

enum class GameState
{
	Title,      // タイトル画面
	Ready,      // 芯車制作画面
	Playing,    // プレイ中
	Rnaking,     // ランキング表示
	None        // 無効な状態
};
