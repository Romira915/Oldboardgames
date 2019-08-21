#pragma once
#include "Task.h"
#include "Coin.h"
#include "OtherInterface.h"
#include "DxLib.h"

#define COIN_IMGNUM 5

#define BOARD_NUM 16
#define COIN_NUM 4 * 7 * 2

#define INIT_SPEED 0.075

class CoinManager : public Task
{
public:
	CoinManager(OtherInterface* OI);
	~CoinManager();

	void Initialize() override;	//初期化
	void Finalize() override;	//終了処理
	void Update() override;		//更新
	void Draw() override;		//描画

private:
	OtherInterface* mOtherInterFace;

	const std::string coin_filepath = "Assets//coin";
	int coinHandle[COIN_IMGNUM];
	VECTOR coindrawpos[BOARD_NUM][4];
	VECTOR coindrawpos5[BOARD_NUM]; // コインが5個以上の位置情報
	Coin** coin;

	unsigned char coinmovecounter;
};