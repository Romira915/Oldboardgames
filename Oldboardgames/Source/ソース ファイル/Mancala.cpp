#include "Mancala.h"
#include "DxLib.h"

Mancala::Mancala(ISceneChanger* changer, OtherInterface* OI) : BaseScene(changer, OI)
{
	coinHandle.resize(4);
	coinMgr = new CoinManager(OI);

	VECTOR tmp[BOARD_NUM][4] = { {{478,765,0},{490,833,0},{546,767,0},{576,833,0}},{{602,611,0},{681,667,0},{675,598,0},{600,676,0}},{{740,771,0},{823,768,0},{744,840,0},{815,838,0}},{{877,679,0},{960,615,0},{875,609,0},{945,681,0}},{{1012,770,0},{1016,835,0},{1085,763,0},{1090,833,0}},{{1151,605,0},{1153,676,0},{1228,606,0},{1225,677,0} },{{ 1379,771,0 }, { 1295,772,0 }, { 1290,838,0 }, { 1365,838,0 }},{{ 1460,437,0 }, { 1567,571,0 }, { 1568,448,0 }, { 1471,568,0 }},{ { 1303,152,0 }, { 1301,218,0 }, { 1382,224,0 }, { 1381,159,0 }},{ { 1172,320,0 }, { 1177,390,0 }, { 1245,385,0 }, { 1247,321,0 }},{ { 1110,232,0 }, { 1118,163,0 }, { 1036,152,0 }, { 1024,219,0 }},{ {981,316,0 }, { 898,319,0 }, { 905,391,0 }, { 976,386,0 }},{ { 842,166,0 }, { 758,163,0 }, { 768,230,0 }, { 837,229,0 }},{ { 627,316,0 }, { 635,385,0 }, { 705,315,0 }, { 703,384,0 }},{ { 485,155,0 }, { 486,229,0 }, { 558,154,0 }, { 559,226,0 }},{{ 315,417,0 }, { 428,572,0 }, { 422,425,0 }, { 315,593,0 }} };
	for (int i = 0; i < BOARD_NUM; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			coindrawpos[i][j].x = tmp[i][j].x / STD_SCREENSIZEX;
			coindrawpos[i][j].y = tmp[i][j].y / STD_SCREENSIZEY;
		}
	}

	logout.open("logpos.txt");
}

Mancala::~Mancala()
{
	logout.close();
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

	coinMgr->Initialize();

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
}

void Mancala::Draw()
{
	DrawRotaGraph2(0, 0, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, boardHandle, TRUE, FALSE);
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
