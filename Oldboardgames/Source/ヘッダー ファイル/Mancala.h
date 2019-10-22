#pragma once
#define _WINSOCK2API_
#include <WinSock2.h>
#include "BaseScene.h"
#include "DxLib.h"
#include <string>
#include <vector>
#include <fstream>
#include "Coin.h"
#include "CoinManager.h"
#include "TCP2.h"

typedef enum {
	ePlayer1Win,
	ePlayer2Win,
	eYouWin,
	eYouLose,

	eUndefined
} VictoryorDefeat;

class Mancala : public BaseScene
{
public:
	Mancala(ISceneChanger* changer, OtherInterface* OI, eMancalaMode mode);
	~Mancala();

	void Initialize() override;    //初期化処理をオーバーライド。
	void Finalize() override;        //終了処理をオーバーライド。
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。

private:
	void CPU();
	int Online();
	void Debug_Update();

	eMancalaMode gamemode; // 0...PvP, 1...vsCPU, 2...Online

	const char* board_filepath = "Assets//manncalaboard.png";
	const char* boardselect_filepath = "Assets//manncalaboard";
	const std::string coin_filepath = "Assets//coin";
	const char* player1_filepath = "Assets//player1.png";
	const char* player2_filepath = "Assets//player2.png";
	const char* you_filepath = "Assets//You.png";
	const char* win_filepath = "Assets//win.png";
	const char* lose_filepath = "Assets//Lose.png";
	int boardHandle;
	int boardselectHandle[BOARD_NUM];
	std::vector<int> coinHandle;
	int player1Handle, player2Handle;
	int youHandle;
	int winHandle, loseHandle;
	int player;
	int player1select, player2select;
	int onlineselect;
	VictoryorDefeat vod;

	CoinManager* coinMgr;

	TCP2 tcp2;
	std::string tcp_message;

	std::ifstream readfile;

	// デバッグ変数
	bool click;
	int x, y;
	std::vector<int> x_array;
	std::vector<int> y_array;
	std::ofstream logout;
};