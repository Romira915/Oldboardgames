#pragma once
#include "Task.h"
#include "Coin.h"
#include "OtherInterface.h"
#include "DxLib.h"

class CoinManager : public Task
{
public:
	CoinManager(OtherInterface* OI);
	~CoinManager();

	void Initialize() override;	//初期化
	void Finalize() override;	//終了処理
	void Update() override;		//更新
	void Draw() override;		//描画

	void SelectHole(int hole);
	int Get_boardstatus(int sub);
	bool All_Rest();

private:
	OtherInterface* mOtherInterFace;

	const std::string coin_filepath = "Assets//coin";
	int coinnumfontHandle;
	int coinHandle[COIN_IMGNUM];
	VECTOR coindrawpos[BOARD_NUM][4]; // コインが４個以下の位置情報
	VECTOR coindrawpos5[BOARD_NUM]; // コインが5個以上の位置情報
	Coin** coin;

	unsigned char coinmovecounter;
	int boardstatus[BOARD_NUM];
};