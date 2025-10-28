#pragma once
# include "UI/Button/Button.h"

/*
// リザルトを表示するヘッダー
*/

class Result
{
public:
	Result();
	bool update();
	void Goal(float cleatTime);

private:
	bool isGoal;
	double time;
	const Font font;
	Button returnTitleButton;
};

