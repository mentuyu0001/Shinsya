#pragma once

/// <summary>
/// ゲームの状態を定義する列挙型
/// </summary>

enum class GameState
{
	Title,      // タイトル画面
	Ready,      // 芯車制作画面
	Playing,    // プレイ中
	Reset,		// リセット
	Ranking,     // ランキング表示
	Explain,    // 説明画面
	None        // 無効な状態
};
