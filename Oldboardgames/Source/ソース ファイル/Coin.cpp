#include "Coin.h"
#include "DxLib.h"

Coin::Coin()
{
	pos.x = 925 / STD_SCREENSIZEX;
	pos.y = 492 / STD_SCREENSIZEY;
}

Coin::~Coin()
{
}

void Coin::Initialize()
{
	coinHandle = LoadGraph((coin_filepath + std::to_string(GetRand(3)) + ".png").c_str());
}

void Coin::Finalize()
{
}

void Coin::Update()
{
	Move::Update();
}

void Coin::Draw()
{
	DrawRotaGraph2(pos.x * SCREEN_SIZEX, pos.y * SCREEN_SIZEY, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX * 0.425, 0, coinHandle, TRUE, FALSE);
}
