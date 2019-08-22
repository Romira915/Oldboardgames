#pragma once
#include "BaseScene.h"
#include "DxLib.h"
#include <string>
#include <vector>
#include <fstream>
#include "Coin.h"
#include "CoinManager.h"

class Mancala : public BaseScene
{
public:
	Mancala(ISceneChanger* changer, OtherInterface* OI);
	~Mancala();

	void Initialize() override;    //�������������I�[�o�[���C�h�B
	void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

private:
	void Debug_Update();

	const char* board_filepath = "Assets//manncalaboard.png";
	const char* boardselect_filepath = "Assets//manncalaboard";
	const std::string coin_filepath = "Assets//coin";
	const char* player1_filepath = "Assets//player1.png";
	const char* player2_filepath = "Assets//player2.png";
	int boardHandle;
	int boardselectHandle[BOARD_NUM];
	std::vector<int> coinHandle;
	int player1Handle, player2Handle;
	int player;
	int player1select, player2select;

	CoinManager* coinMgr;

	// �f�o�b�O�ϐ�
	bool click;
	int x, y;
	std::vector<int> x_array;
	std::vector<int> y_array;
	std::ofstream logout;
};