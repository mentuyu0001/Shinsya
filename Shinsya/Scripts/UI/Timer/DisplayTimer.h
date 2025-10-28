#pragma once

/*
// タイマーを表示するヘッダー
*/

class DisplayTimer
{
public:
	DisplayTimer();
	void draw() const;
	void Goal();
	bool getIsGoal() const;
	void addTime();
	float getTime() const;

private:
	bool isGoal;
	double time;
	const Font font;
};

