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
		font(U"Time: {:.2f}"_fmt(time)).draw(40, Vec2{ 40, 40 }, Palette::Black);
	}
	else
	{
		font(U"Time: {:.2f}"_fmt(Scene::Time())).draw(40, Vec2{ 40, 40 }, Palette::Black);
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
