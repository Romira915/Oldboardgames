#include "Mancala.h"
#include "DxLib.h"

Mancala::Mancala(ISceneChanger* changer, OtherInterface* OI) : BaseScene(changer, OI)
{
	coinHandle.resize(4);
	coinMgr = new CoinManager(OI);

	logout.open("logpos.txt");
}

Mancala::~Mancala()
{
	logout.close();
}

void Mancala::Initialize()
{
	boardHandle = LoadGraph(board_filepath);
	for (int i = 0; i < BOARD_NUM; i++)
	{
		boardselectHandle[i] = LoadGraph((boardselect_filepath + std::to_string(i) + ".png").c_str());
	}
	for (int i = 0; i < coinHandle.size(); i++)
	{
		coinHandle[i] = LoadGraph((coin_filepath + std::to_string(i) + ".png").c_str());
	}

	player1Handle = LoadGraph(player1_filepath);
	player2Handle = LoadGraph(player2_filepath);

	coinMgr->Initialize();
	player = GetRand(1);
	player1select = 0;
	player2select = 8;

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

	coinMgr->Finalize();
}

void Mancala::Update()
{
	if (mOtherInterface->KeyDown(KEY_INPUT_ESCAPE))
	{
		mSceneChanger->ChangeScene(eScene_Title);
	}
	//Debug_Update();	

	coinMgr->Update();

	if (coinMgr->All_Rest())
	{
		if (player == 0)
		{
			if (mOtherInterface->KeyDown(KEY_INPUT_LEFT))
			{
				player1select = ((player1select + 7) - 1) % 7;
			}
			else if (mOtherInterface->KeyDown(KEY_INPUT_RIGHT))
			{
				player1select = (player1select + 1) % 7;
			}
			else if (mOtherInterface->KeyDown(KEY_INPUT_RETURN) && coinMgr->Get_boardstatus(player1select))
			{
				coinMgr->SelectHole(player1select);
				player = (player + 1) % 2;
			}
		}
		else if (player == 1)
		{
			if (mOtherInterface->KeyDown(KEY_INPUT_LEFT))
			{
				player2select = (player2select - 8 + 1) % 7 + 8;
			}
			else if (mOtherInterface->KeyDown(KEY_INPUT_RIGHT))
			{
				player2select = (player2select - 8 + 7 - 1) % 7 + 8;
			}
			else if (mOtherInterface->KeyDown(KEY_INPUT_RETURN) && coinMgr->Get_boardstatus(player2select))
			{
				coinMgr->SelectHole(player2select);
				player = (player + 1) % 2;
			}
		}
	}
}

void Mancala::Draw()
{
	DrawRotaGraph2(0, 0, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, boardHandle, TRUE, FALSE);
	if (player == 0 && coinMgr->All_Rest())
	{
		DrawRotaGraph2(0, 0, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, boardselectHandle[player1select], TRUE, FALSE);
	}
	if (player == 1 && coinMgr->All_Rest())
	{
		DrawRotaGraph2(0, 0, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, boardselectHandle[player2select], TRUE, FALSE);
	}
	DrawRotaGraph2(SCREEN_SIZEX * PLAYER1_IMGX, SCREEN_SIZEY * PLAYER12_IMGY, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, player1Handle, TRUE, FALSE);
	DrawRotaGraph2(SCREEN_SIZEX * PLAYER2_IMGX, SCREEN_SIZEY * PLAYER12_IMGY, 335, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, player2Handle, TRUE, FALSE);

	// デバッグ用
	/*for (int i = 0; i < x_array.size(); i++)
	{
		DrawRotaGraph2(x_array[i], y_array[i], 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX * 0.425, 0, coinHandle[0], TRUE, FALSE);
	}*/

	coinMgr->Draw();
}

void Mancala::Debug_Update()
{
	if (mOtherInterface->KeyDown(KEY_INPUT_R))
	{
		click = false;
	}
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && click == false)
	{
		click = true;
		GetMousePoint(&x, &y);
		x_array.push_back(x);
		y_array.push_back(y);
	}
	if (mOtherInterface->KeyDown(KEY_INPUT_D))
	{
		x_array.pop_back();
		y_array.pop_back();
	}
	if (mOtherInterface->KeyDown(KEY_INPUT_W))
	{
		for (int i = 0; i < x_array.size(); i++)
		{
			printfDx("%d,%d ", x_array[i], y_array[i]);
			if ((i + 1) % 4 == 0)
			{
				printfDx("\n");
			}
		}
		logout << '{';
		for (int i = 0; i < x_array.size(); i++)
		{
			logout << '{' << x_array[i] << ',' << y_array[i] << ',' << 0 << "},";
		}
		logout << '}';
	}
}
