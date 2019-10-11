#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <Winsock2.h>

#include "Mancala.h"
#include "DxLib.h"

Mancala::Mancala(ISceneChanger* changer, OtherInterface* OI, eMancalaMode mode) : BaseScene(changer, OI)
{
	coinHandle.resize(4);
	coinMgr = new CoinManager(OI);
	gamemode = mode;
	tcp_message = "null";

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
	youHandle = LoadGraph(you_filepath);
	winHandle = LoadGraph(win_filepath);
	loseHandle = LoadGraph(lose_filepath);

	coinMgr->Initialize();
	player = GetRand(1);
	player1select = 0;
	player2select = 8;
	onlineselect = -1;
	vod = eUndefined;

	click = false;

	tcp2.Initialize();
	if (gamemode == eOnline)
	{
		tcp2.Client_connect(std::string(SERVER_IP));
	}
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

	tcp2.Finalize();
}

void Mancala::Update()
{
	//clsDx();
	if (mOtherInterface->KeyDown(KEY_INPUT_ESCAPE))
	{
		mSceneChanger->ChangeScene(eScene_Title);
	}
	//Debug_Update();	

	coinMgr->Update();
	tcp2.Update();

	if (tcp2.Get_TCPstatus() == eReceived)
	{
		tcp_message = tcp2.Get_message();
		printfDx("%sを受信\n", tcp_message.c_str());

		if (tcp_message == "server")
		{
			player = 1;
			printfDx("listen\n");
			tcp2.Server_listen(60000);
		}
		else if (tcp_message.find_first_of("ip") == 0)
		{
			player = 0;
			tcp2.Client_connect(tcp_message.substr(2), 60000);
		}
		else
		{
			onlineselect = stoi(tcp_message);
			printfDx("数値%dに変換\n", onlineselect);
			if (!(onlineselect >= 8 && onlineselect <= 14))
			{
				onlineselect = -1;
			}
		}
	}

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
				if (gamemode != eOnline || (gamemode == eOnline && tcp2.Get_TCPstatus() == eConnected))
				{
					if ((player1select + coinMgr->Get_boardstatus(player1select)) % 8 != 7)
					{
						player = (player + 1) % 2;
					}
					coinMgr->SelectHole(player1select);
					if (gamemode == eOnline && tcp2.Get_TCPstatus() == eConnected)
					{
						tcp2.Send_message(std::to_string(player1select + 8));
					}

				}
			}
		}
		else if (player == 1)
		{
			switch (gamemode)
			{
			case ePvP:
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
					if ((player2select + coinMgr->Get_boardstatus(player2select)) % 8 != 7)
					{
						player = (player + 1) % 2;
					}
					coinMgr->SelectHole(player2select);
				}
				break;
			case eCPU:
				CPU();
				if ((player2select + coinMgr->Get_boardstatus(player2select)) % 8 != 7)
				{
					player = (player + 1) % 2;
				}
				break;
			case eOnline:
			{
				if (tcp2.Get_TCPstatus() == eConnected)
				{
					int tmpselect = -1;
					if ((tmpselect = Online()) != -1)
					{
						player2select = tmpselect;
						printfDx("player2select:%d\n", player2select);
						if ((player2select + coinMgr->Get_boardstatus(player2select)) % 8 != 7)
						{
							player = (player + 1) % 2;
						}
						printfDx("%d\n", player2select);
						coinMgr->SelectHole(player2select);
					}
				}
			}
			break;
			default:
				break;
			}

		}

		for (int i = 0; i < 7; i++)
		{
			if (coinMgr->Get_boardstatus(i) != 0)
			{
				break;
			}

			if (i == 7 - 1)
			{
				if (gamemode == ePvP)
				{
					vod = ePlayer1Win;
				}
				else
				{
					vod = eYouWin;
				}
			}
		}
		for (int i = 8; i < 16; i++)
		{
			if (coinMgr->Get_boardstatus(i) != 0)
			{
				break;
			}

			if (i == 16 - 1)
			{
				if (gamemode == ePvP)
				{
					vod = ePlayer2Win;
				}
				else
				{
					vod = eYouLose;
				}
			}
		}
	}

	if (mOtherInterface->KeyDown(KEY_INPUT_V))
	{
		vod = ePlayer1Win;
	}
	if (mOtherInterface->KeyDown(KEY_INPUT_B))
	{
		vod = ePlayer2Win;
	}
	if (mOtherInterface->KeyDown(KEY_INPUT_N))
	{
		vod = eYouWin;
	}
	if (mOtherInterface->KeyDown(KEY_INPUT_M))
	{
		vod = eYouLose;
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

	if (gamemode == ePvP)
	{
		DrawRotaGraph2(SCREEN_SIZEX * PLAYER1_IMGX, SCREEN_SIZEY * PLAYER12_IMGY, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, player1Handle, TRUE, FALSE);
	}
	else
	{
		DrawRotaGraph2(SCREEN_SIZEX * PLAYER1_IMGX, SCREEN_SIZEY * PLAYER12_IMGY, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, youHandle, TRUE, FALSE);
	}
	DrawRotaGraph2(SCREEN_SIZEX * PLAYER2_IMGX, SCREEN_SIZEY * PLAYER12_IMGY, 335, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, player2Handle, TRUE, FALSE);

	// デバッグ用
	/*for (int i = 0; i < x_array.size(); i++)
	{
		DrawRotaGraph2(x_array[i], y_array[i], 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX * 0.425, 0, coinHandle[0], TRUE, FALSE);
	}*/

	coinMgr->Draw();

	switch (vod)
	{
	case ePlayer1Win:
		DrawRotaGraph2(SCREEN_SIZEX * PlAYER12YOU_WINX - (333.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX * 0.75), SCREEN_SIZEY * PlAYER12YOU_WINY - (101.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX * 0.75), 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX * 0.75, 0, player1Handle, TRUE, FALSE);
		DrawRotaGraph2(SCREEN_SIZEX * WINLOSE_IMGX - (184.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX), SCREEN_SIZEY * WINLOSE_IMGY- (86.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX * 0.75), 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, winHandle, TRUE, FALSE);
		break;
	case ePlayer2Win:
		DrawRotaGraph2(SCREEN_SIZEX * PlAYER12YOU_WINX - (335.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX * 0.75), SCREEN_SIZEY * PlAYER12YOU_WINY- (101.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX * 0.75), 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX * 0.75, 0, player2Handle, TRUE, FALSE);
		DrawRotaGraph2(SCREEN_SIZEX * WINLOSE_IMGX - (184.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX), SCREEN_SIZEY * WINLOSE_IMGY- (86.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX * 0.75), 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, winHandle, TRUE, FALSE);
		break;
	case eYouWin:
		DrawRotaGraph2(SCREEN_SIZEX * PlAYER12YOU_WINX - (161 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX * 0.75), SCREEN_SIZEY * PlAYER12YOU_WINY- (79.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX * 0.75), 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX * 0.75, 0, youHandle, TRUE, FALSE);
		DrawRotaGraph2(SCREEN_SIZEX * WINLOSE_IMGX - (184.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX), SCREEN_SIZEY * WINLOSE_IMGY- (86.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX * 0.75), 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, winHandle, TRUE, FALSE);
		break;
	case eYouLose:
		DrawRotaGraph2(SCREEN_SIZEX * PlAYER12YOU_WINX - (161 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX * 0.75), SCREEN_SIZEY * PlAYER12YOU_WINY- (79.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX * 0.75), 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX * 0.75, 0, youHandle, TRUE, FALSE);
		DrawRotaGraph2(SCREEN_SIZEX * WINLOSE_IMGX - (193.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX), SCREEN_SIZEY * WINLOSE_IMGY- (84.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX * 0.75), 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, loseHandle, TRUE, FALSE);
		break;
	default:
		break;
	}

	tcp2.Draw();
}

void Mancala::CPU()
{
	for (int i = BOARD_NUM - 2; i >= BOARD_NUM / 2; i--)
	{
		if ((i + coinMgr->Get_boardstatus(i)) % 8 == 7)
		{
			coinMgr->SelectHole(i);
			player2select = i;
			return;
		}
	}
	for (int i = BOARD_NUM / 2; i < BOARD_NUM - 1; i++)
	{
		if ((i + coinMgr->Get_boardstatus(i) + 1) % 8 == 7)
		{
			for (int j = i - 1; j > 7; j--)
			{
				if (j + coinMgr->Get_boardstatus(j) == i)
				{
					coinMgr->SelectHole(j);
					player2select = j;
					return;
				}
			}
		}
	}
	int r;
	while (true)
	{
		r = GetRand(6) + 8;
		if (coinMgr->Get_boardstatus(r) > 0)
		{
			break;
		}
	}
	coinMgr->SelectHole(r);
	player2select = r;
}

int Mancala::Online()
{
	int tmp = onlineselect;
	onlineselect = -1;

	return tmp;
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