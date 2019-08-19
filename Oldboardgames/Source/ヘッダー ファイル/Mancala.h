#pragma once
#include "BaseScene.h"
#include "DxLib.h"
#include <string>
#include <vector>
#include <fstream>
#include "Coin.h"

#define COIN_IMGNUM 5 

#define PLAYER1_IMGX 0.04
#define PLAYER2_IMGX 0.96
#define PLAYER12_IMGY 0.03

#define COIN_NUM 14 * 4
#define BOARD_NUM 16


class Mancala : public BaseScene
{
public:
	Mancala(ISceneChanger* changer, OtherInterface* OI);
	~Mancala();

	void Initialize() override;    //初期化処理をオーバーライド。
	void Finalize() override;        //終了処理をオーバーライド。
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。

private:
	void Debug_Update();

	const char* board_filepath = "Assets//manncalaboard.png";
	const std::string coin_filepath = "Assets//coin";
	const char* player1_filepath = "Assets//player1.png";
	const char* player2_filepath = "Assets//player2.png";
	int boardHandle;
	std::vector<int> coinHandle;
	int player1Handle, player2Handle;

	int boardstatus[BOARD_NUM]; // 左下赤を0とする
	VECTOR coindrawpos[BOARD_NUM][4];
	Coin coin[COIN_NUM];

	// デバッグ変数
	bool click;
	int x, y;
	std::vector<int> x_array;
	std::vector<int> y_array;
	std::ofstream logout;
};