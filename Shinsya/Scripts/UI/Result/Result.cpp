#include "stdafx.h"

/*
// リザルト画面を表示するスクリプト
*/

Result::Result()
	: isGoal(false),
	  time(0),
	  font({ FontMethod::MSDF, 72, Typeface::Bold }),
	  returnTitleButton({ RectF{ Arg::center = Scene::Center().movedBy(0, 100), 300, 80 }, Font{ 48, Typeface::Bold }, U"タイトルに戻る" })
{
}

bool Result::update()
{
	if (isGoal)
	{
		Rect{ 0, 0, 1280, 720 }.draw(ColorF{ 0, 0, 0, 0.5 });
		font(U"クリア！"_fmt(time)).draw(80, Arg::center = Scene::Center().movedBy(0, -150), ColorF{ 1, 0.7, 0.7});
		font(U"タイム: {:.2f}秒"_fmt(time)).draw(40, Arg::center = Scene::Center().movedBy(0, 0), Palette::White);
		if (returnTitleButton.update())
		{
			return true;
		}
		return false;
	}
}

void Result::Goal(float clearTime)
{
	isGoal = true;
	time = clearTime;
}
