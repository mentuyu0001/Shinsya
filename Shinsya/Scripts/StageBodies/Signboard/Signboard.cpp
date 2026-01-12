#include "stdafx.h"
#include "Signboard.h"

Signboard::Signboard(int in_x, int in_y, float in_scale)
	: texture(U"Assets/Images/Stage/OperatingUI.png")
	, pos_x(in_x)
	, pos_y(in_y)
	, scale(in_scale)
{
}

void Signboard::draw() const
{
	texture.scaled(scale).draw(pos_x, pos_y);
}
