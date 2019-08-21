#include "Coin.h"
#include "DxLib.h"

Coin::Coin(int Handle)
{
	coinHandle = Handle;
	postype = -1;
}

Coin::~Coin()
{
}

void Coin::Initialize()
{
	pos.x = 925 / STD_SCREENSIZEX;
	pos.y = 492 / STD_SCREENSIZEY;
	coinHandle = LoadGraph((coin_filepath + std::to_string(GetRand(3)) + ".png").c_str());
}

void Coin::Finalize()
{
	DeleteGraph(coinHandle);
}

void Coin::Update()
{
	Move::Update();
}

void Coin::Draw()
{
	DrawRotaGraph2(pos.x * SCREEN_SIZEX, pos.y * SCREEN_SIZEY, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX * 0.425, 0, coinHandle, TRUE, FALSE);
}

void Coin::Set_postype(unsigned char set)
{
	if (set >= 0 && set < BOARD_NUM)
	{
		postype = set;
	}
	else
	{
		DxLib_End();
		exit(-1);
	}
}

int Coin::Get_postype()
{
	return postype;
}
