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