#include "Move.h"

Move::Move()
{
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

	}
}

void Move::Draw()
{
}

void Move::Move_toP(int x, int y, int speed)
{
	if (moving == false)
	{
		moving = true;
		dist_x = x;
		dist_y = y;
		movespeed = speed;
	}
}

bool Move::Whether_moving()
{
	return moving;
}
