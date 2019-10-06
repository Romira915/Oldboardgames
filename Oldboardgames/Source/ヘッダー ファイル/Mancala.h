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
#include "TCP.h"

class Mancala : public BaseScene
{
public:
	Mancala(ISceneChanger* changer, OtherInterface* OI, eMancalaMode mode);
	~Mancala();

	void Initialize() override;    //�������������I�[�o�[���C�h�B
	void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

private:
	void CPU();
	void Debug_Update();

	eMancalaMode gamemode; // 0...PvP, 1...vsCPU, 2...Online

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

	std::string tcp_message;
	eTCPmode tcp_mode;

	//�J����
	void net();
	WSADATA wsaData;
	SOCKET sock;
	TCP tcp;


	// �f�o�b�O�ϐ�
	bool click;
	int x, y;
	std::vector<int> x_array;
	std::vector<int> y_array;
	std::ofstream logout;
};