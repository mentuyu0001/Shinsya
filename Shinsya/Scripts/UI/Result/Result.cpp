#include "stdafx.h"
#include "Result.h"

/*
// リザルト画面を表示するスクリプト
*/

Result::Result()
	: isGoal(false),
	  time(0),
	  font({ FontMethod::MSDF, 72, Typeface::Bold }),
	  returnTitleButton({ RectF{ Arg::center = Scene::Center().movedBy(200, 100), 300, 80 }, Font{ 40, Typeface::Bold }, U"タイトルに戻る" }),
	  resetButton({ RectF{ Arg::center = Scene::Center().movedBy(-200, 100), 300, 80 }, Font{ 40, Typeface::Bold }, U"リトライ" })
{
}

bool Result::titleUpdate()
{
	if (isGoal)
	{
		if (returnTitleButton.update())
		{
			return true;
		}
		return false;
	}
}

bool Result::resetUpdate()
{
	if (isGoal)
	{
		if (resetButton.update())
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

void Result::draw() const
{
	if (isGoal)
	{
		Rect{ 0, 0, 1280, 720 }.draw(ColorF{ 0, 0, 0, 0.5 });
		font(U"クリア！"_fmt(time)).draw(80, Arg::center = Scene::Center().movedBy(0, -150), ColorF{ 1, 0.7, 0.7 });
		font(U"タイム: {:.2f}秒"_fmt(time)).draw(48, Arg::center = Scene::Center().movedBy(0, -20), Palette::White);
		returnTitleButton.draw();
		resetButton.draw();
	}
}
