#include "stdafx.h"

/*
// タイマーを表示するスクリプト
*/

DisplayTimer::DisplayTimer()
	: isGoal(false),
	  time(0),
	  font({ FontMethod::MSDF, 48, Typeface::Bold })
{

}

void DisplayTimer::draw() const
{
	if (isGoal)
	{
		font(U"タイム: {:.2f}秒"_fmt(time)).draw(40, Vec2{ 40, 40 }, Palette::Black);
	}
	else
	{
		font(U"タイム: {:.2f}秒"_fmt(Scene::Time())).draw(40, Vec2{ 40, 40 }, Palette::Black);
	}
}

void DisplayTimer::Goal()
{
	isGoal = true;
}

bool DisplayTimer::getIsGoal() const
{
	return isGoal;
}

void DisplayTimer::addTime()
{
	if (!isGoal)
	{
		time += Scene::DeltaTime();
	}
}

float DisplayTimer::getTime() const
{
	return time;
}
