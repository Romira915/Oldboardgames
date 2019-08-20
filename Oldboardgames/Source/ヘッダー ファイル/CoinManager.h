#pragma once
#include "Task.h"
#include "coin.h"
#include "DxLib.h"

#define BOARD_NUM 16

class CoinManager : public Task
{
public:
	CoinManager();
	~CoinManager();

	void Initialize() override;	//初期化
	void Finalize() override;	//終了処理
	void Update() override;		//更新
	void Draw() override;		//描画

private:
	VECTOR coindrawpos[BOARD_NUM][4];
	VECTOR coindrawpos5[BOARD_NUM]; // コインが5個以上の位置情報
};

