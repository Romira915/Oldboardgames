#pragma once
#include "BaseScene.h"
#include <string>
#include <vector>

#define COIN_SIZE 4

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
	const char* board_filepath = "Assets//manncalaboard.png";
	const std::string coin_filepath = "Assets//coin";
	int boardHandle;
	std::vector<int> coinHandle;
};