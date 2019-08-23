#include "CoinManager.h"

CoinManager::CoinManager(OtherInterface* OI)
{
	mOtherInterFace = OI;

	VECTOR tmp[BOARD_NUM][4] = { {{478,765,0},{490,833,0},{546,767,0},{576,833,0}},{{602,611,0},{681,667,0},{675,598,0},{600,676,0}},{{740,771,0},{823,768,0},{744,840,0},{815,838,0}},{{877,679,0},{960,615,0},{875,609,0},{945,681,0}},{{1012,770,0},{1016,835,0},{1085,763,0},{1090,833,0}},{{1151,605,0},{1153,676,0},{1228,606,0},{1225,677,0} },{{ 1379,771,0 }, { 1295,772,0 }, { 1290,838,0 }, { 1365,838,0 }},{{ 1460,437,0 }, { 1567,571,0 }, { 1568,448,0 }, { 1471,568,0 }},{ { 1303,152,0 }, { 1301,218,0 }, { 1382,224,0 }, { 1381,159,0 }},{ { 1172,320,0 }, { 1177,390,0 }, { 1245,385,0 }, { 1247,321,0 }},{ { 1110,232,0 }, { 1118,163,0 }, { 1036,152,0 }, { 1024,219,0 }},{ {981,316,0 }, { 898,319,0 }, { 905,391,0 }, { 976,386,0 }},{ { 842,166,0 }, { 758,163,0 }, { 768,230,0 }, { 837,229,0 }},{ { 627,316,0 }, { 635,385,0 }, { 705,315,0 }, { 703,384,0 }},{ { 485,155,0 }, { 486,229,0 }, { 558,154,0 }, { 559,226,0 }},{{ 315,417,0 }, { 428,572,0 }, { 422,425,0 }, { 315,593,0 }} };
	for (int i = 0; i < BOARD_NUM; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			coindrawpos[i][j].x = tmp[i][j].x / STD_SCREENSIZEX;
			coindrawpos[i][j].y = tmp[i][j].y / STD_SCREENSIZEY;
		}
	}
	VECTOR tmp2[BOARD_NUM] = { {473,803,0},{599,639,0},{725,802,0},{868,638,0},{1007,803,0},{1145,644,0},{1284,800,0},{1447,500,0},{1290,191,0},{1161,351,0},{1032,193,0},{890,352,0},{755,188,0},{620,354,0},{470,194,0},{294,504,0}, };
	for (int i = 0; i < BOARD_NUM; i++)
	{
		coindrawpos5[i].x = tmp2[i].x / STD_SCREENSIZEX;
		coindrawpos5[i].y = tmp2[i].y / STD_SCREENSIZEY;
	}

	for (int i = 0; i < COIN_IMGNUM; i++)
	{
		coinHandle[i] = LoadGraph((coin_filepath + std::to_string(GetRand(COIN_IMGNUM - 1)) + ".png").c_str());
	}

	coin = new Coin * [COIN_NUM];
	for (int i = 0; i < COIN_NUM; i++)
	{
		coin[i] = new Coin(coinHandle[GetRand(COIN_IMGNUM - 1)]);
	}

	coinnumfontHandle = CreateFontToHandle(NULL, COINFONTSIZE * SCREEN_SIZEX, -1, DX_FONTTYPE_EDGE);
}

CoinManager::~CoinManager()
{
	for (int i = 0; i < COIN_NUM; i++)
	{
		delete coin[i];
	}
	delete[] coin;

	for (int i = 0; i < COIN_IMGNUM; i++)
	{
		DeleteGraph(coinHandle[i]);
	}
}

void CoinManager::Initialize()
{
	for (int i = 0; i < COIN_NUM; i++)
	{
		coin[i]->Initialize();
	}

	coinmovecounter = 0;
}

void CoinManager::Finalize()
{
	for (int i = 0; i < COIN_NUM; i++)
	{
		coin[i]->Finalize();
	}
}

void CoinManager::Update()
{
	for (int i = 0; i < COIN_NUM; i++)
	{
		coin[i]->Update();
	}
	// ボード上の穴別のコインの数を取得
	for (int i = 0; i < BOARD_NUM; i++)
	{
		boardstatus[i] = 0;
		for (int j = 0; j < COIN_NUM; j++)
		{
			if (i == coin[j]->Get_postype())
			{
				boardstatus[i]++;
			}
		}
	}
	// 初期状態へ移動
	for (int i = 0; i < COIN_NUM && coinmovecounter != COIN_NUM; i++)
	{
		if (coinmovecounter == 0 || (coinmovecounter > 0 && !coin[coinmovecounter - 1]->Whether_moving()))
		{
			if (coinmovecounter / 4 >= 7)
			{
				coin[coinmovecounter]->Move_toP(coindrawpos[coinmovecounter / 4 + 1][coinmovecounter % 4].x, coindrawpos[coinmovecounter / 4 + 1][coinmovecounter % 4].y, INIT_SPEED);
				coin[coinmovecounter]->Set_postype(coinmovecounter / 4 + 1);
				coinmovecounter++;
			}
			else
			{
				coin[coinmovecounter]->Move_toP(coindrawpos[coinmovecounter / 4][coinmovecounter % 4].x, coindrawpos[coinmovecounter / 4][coinmovecounter % 4].y, INIT_SPEED);
				coin[coinmovecounter]->Set_postype(coinmovecounter / 4);
				coinmovecounter++;
			}
		}
		if (mOtherInterFace->KeyDown(KEY_INPUT_RETURN))
		{
			for (int i = 0, k = 0; i < BOARD_NUM - 1; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (i != 7)
					{
						if (k >= 0 && k < COIN_NUM)
						{
							coin[k]->Move_toP(coindrawpos[i][j].x, coindrawpos[i][j].y, INIT_SPEED);
							coin[k]->Set_postype(i);
							k++;
						}
					}
				}
			}
			coinmovecounter = COIN_NUM;
		}
	}
	// postypeの位置へ移動
	for (int i = 0; i < BOARD_NUM && coinmovecounter == COIN_NUM; i++)
	{
		if (!All_Rest())
		{
			break;
		}
		if (boardstatus[i] <= 4)
		{
			for (int j = 0, num = 0; j < COIN_NUM; j++)
			{
				if (i == coin[j]->Get_postype())
				{
					coin[j]->Move_toP(coindrawpos[i][num].x, coindrawpos[i][num].y, SPEED);
					coin[j]->Set_postype(i);
					num++;
				}
			}
		}
		else
		{
			for (int j = 0; j < COIN_NUM; j++)
			{
				if (i == coin[j]->Get_postype())
				{
					coin[j]->Move_toP(coindrawpos5[i].x, coindrawpos5[i].y, SPEED);
					coin[j]->Set_postype(i);
				}
			}
		}
	}
}

void CoinManager::Draw()
{
	for (int i = 0; i < COIN_NUM; i++)
	{
		coin[i]->Draw();
	}
	for (int i = 0; i < BOARD_NUM; i++)
	{
		if (boardstatus[i] >= 5 && All_Rest())
		{
			DrawFormatStringToHandle(coindrawpos5[i].x * SCREEN_SIZEX + 150 * SCREEN_SIZEX / STD_SCREENSIZEX * 0.425, coindrawpos5[i].y * SCREEN_SIZEY, GetColor(0, 128, 0), coinnumfontHandle, "×%d", boardstatus[i]);
		}
	}
}

void CoinManager::SelectHole(int hole)
{
	for (int i = 0, holenum = hole + 1; i < COIN_NUM; i++)
	{
		if (coin[i]->Get_postype() == hole)
		{
			coin[i]->Set_postype(holenum);
			holenum++;
		}
	}
}

int CoinManager::Get_boardstatus(int sub)
{
	return boardstatus[sub];
}

bool CoinManager::All_Rest()
{
	for (int i = 0; i < COIN_NUM; i++)
	{
		if (coin[i]->Whether_moving())
		{
			return false;
		}
	}
	return true;
}
