#include "Stone.h"
#include "DxLib.h"

Stone::Stone()
{
}

Stone::~Stone()
{
}

void Stone::Initialize()
{
	coinHandle = LoadGraph((coin_filepath + std::to_string(GetRand(3)) + ".png").c_str());
}

void Stone::Finalize()
{
}

void Stone::Update()
{
	Move::Update();
}

void Stone::Draw()
{
	DrawRotaGraph2(pos.x, pos.y, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX * 0.425, 0, coinHandle, TRUE, FALSE);
}
