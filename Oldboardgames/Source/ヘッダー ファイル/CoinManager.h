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

	void SelectHole(int hole);
	int Get_boardstatus(int sub);
	bool All_Rest();

private:
	OtherInterface* mOtherInterFace;

	const std::string coin_filepath = "Assets//coin";
	int coinnumfontHandle;
	int coinHandle[COIN_IMGNUM];
	VECTOR coindrawpos[BOARD_NUM][4]; // �R�C�����S�ȉ��̈ʒu���
	VECTOR coindrawpos5[BOARD_NUM]; // �R�C����5�ȏ�̈ʒu���
	Coin** coin;

	unsigned char coinmovecounter;
	int boardstatus[BOARD_NUM];
};