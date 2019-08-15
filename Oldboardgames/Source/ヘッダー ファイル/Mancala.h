#pragma once
#include "BaseScene.h"
#include "DxLib.h"
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>

#define COIN_IMGNUM 5 

#define PLAYER1_IMGX 0.04
#define PLAYER2_IMGX 0.96
#define PLAYER12_IMGY 0.03

#define COIN_NUM 14 * 4


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
	const char* board_filepath = "Assets//manncalaboard.png";
	const std::string coin_filepath = "Assets//coin";
	const char* player1_filepath = "Assets//player1.png";
	const char* player2_filepath = "Assets//player2.png";
	int boardHandle;
	std::vector<int> coinHandle;
	int player1Handle, player2Handle;
	
	int boardstatus[16]; // �����Ԃ�0�Ƃ���
	VECTOR boarddrawpos[16][4];
	
	bool click;
	std::vector<int> x;
	std::vector<int> y;
};