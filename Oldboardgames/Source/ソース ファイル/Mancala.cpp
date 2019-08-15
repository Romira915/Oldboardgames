#include "Mancala.h"
#include "DxLib.h"

Mancala::Mancala(ISceneChanger* changer, OtherInterface* OI) : BaseScene(changer, OI)
{
	coinHandle.resize(4);
}

Mancala::~Mancala()
{
}

void Mancala::Initialize()
{
	boardHandle = LoadGraph(board_filepath);
	for (int i = 0; i < coinHandle.size(); i++)
	{
		coinHandle[i] = LoadGraph((coin_filepath + std::to_string(i) + ".png").c_str());
	}
	player1Handle = LoadGraph(player1_filepath);
	player2Handle = LoadGraph(player2_filepath);

	for (int i = 0; i < 16; i++)
	{
		boardstatus[i] = 4;
	}
	boardstatus[7] = 0;
	boardstatus[15] = 0;

	click = false;
}

void Mancala::Finalize()
{
	DeleteGraph(boardHandle);
	for (int i = 0; i < coinHandle.size(); i++)
	{
		DeleteGraph(coinHandle[i]);
	}
	DeleteGraph(player1Handle);
	DeleteGraph(player2Handle);

}

void Mancala::Update()
{
	if (mOtherInterface->KeyDown(KEY_INPUT_ESCAPE))
	{
		mSceneChanger->ChangeScene(eScene_Title);
	}

	if (mOtherInterface->KeyDown(KEY_INPUT_R))
	{
		click = false;
	}
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && click == false)
	{
		click = true;
		//GetMousePoint(&x, &y);
		printfDx("%d,%d ", x, y);
	}
}

void Mancala::Draw()
{
	DrawRotaGraph2(0, 0, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, boardHandle, TRUE, FALSE);
	DrawRotaGraph2(SCREEN_SIZEX * PLAYER1_IMGX, SCREEN_SIZEY * PLAYER12_IMGY, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, player1Handle, TRUE, FALSE);
	DrawRotaGraph2(SCREEN_SIZEX * PLAYER2_IMGX, SCREEN_SIZEY * PLAYER12_IMGY, 335, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, player2Handle, TRUE, FALSE);

	DrawRotaGraph2(SCREEN_SIZEX * 0.325, SCREEN_SIZEY * 0.3, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX * 0.43, 0, coinHandle[GetRand(3)], TRUE, FALSE);
}
