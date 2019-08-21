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

	void Initialize() override;	//������
	void Finalize() override;	//�I������
	void Update() override;		//�X�V
	void Draw() override;		//�`��


private:
	OtherInterface* mOtherInterFace;

	const std::string coin_filepath = "Assets//coin";
	int coinHandle[COIN_IMGNUM];
	VECTOR coindrawpos[BOARD_NUM][4];
	VECTOR coindrawpos5[BOARD_NUM]; // �R�C����5�ȏ�̈ʒu���
	Coin** coin;

	unsigned char coinmovecounter;
};