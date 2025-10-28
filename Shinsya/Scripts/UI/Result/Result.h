#pragma once
# include "UI/Button/Button.h"

/*
// リザルトを表示するヘッダー
*/

class Result
{
public:
	Result();
	bool titleUpdate();
	bool resetUpdate();
	void draw() const;
	void Goal(float cleatTime);

private:
	bool isGoal;
	double time;
	const Font font;
	Button returnTitleButton;
	Button resetButton;
};

