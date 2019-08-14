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
}

void Mancala::Finalize()
{
}

void Mancala::Update()
{
	if (mOtherInterface->KeyDown(KEY_INPUT_ESCAPE))
	{
		mSceneChanger->ChangeScene(eScene_Title);
	}
}

void Mancala::Draw()
{
	DrawRotaGraph2(0, 0, 0, 0, SCREEN_SIZEX / 1920.0, 0, boardHandle, TRUE, FALSE);
}
