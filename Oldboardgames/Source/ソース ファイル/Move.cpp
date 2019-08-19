#include "Move.h"
#include <cmath>

Move::Move()
{
	moving = false;
}

Move::Move(VECTOR inputpos)
{
	pos = inputpos;
	moving = false;
}

Move::~Move()
{
}

void Move::Initialize()
{
}

void Move::Finalize()
{
}

void Move::Update()
{
	if (moving)
	{
		/*if (counter < maxframe)
		{*/
		if (abs(delta_x) > fabs(dist_x - pos.x))
		{
			pos.x = dist_x;
			pos.y = dist_y;
			moving = false;
			printfDx("%f,%f", pos.x, pos.y);
		}
		else
		{
			pos.x += delta_x;
			pos.y += delta_y;
		}
		//}
	}
}

void Move::Draw()
{
}

void Move::Move_toP(double x, double y, double speed)
{
	if (moving == false)
	{
		moving = true;
		counter = 0;
		dist_x = x;
		dist_y = y;
		movespeed = speed; // ‘¬“x
		maxframe = sqrt(pow(dist_x - pos.x,2) + pow(dist_y - pos.y,2)) / movespeed; // ŽÀŽ¿‚ÌˆÚ“®ŽžŠÔ
		if (maxframe == 0)
		{
			moving = false;
			return;
		}
		delta_x = (dist_x - pos.x) / maxframe;
		delta_y = (dist_y - pos.y) / maxframe;
	}
}

bool Move::Whether_moving()
{
	return moving;
}
