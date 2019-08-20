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

	void Initialize() override;	//������
	void Finalize() override;	//�I������
	void Update() override;		//�X�V
	void Draw() override;		//�`��

private:
	VECTOR coindrawpos[BOARD_NUM][4];
	VECTOR coindrawpos5[BOARD_NUM]; // �R�C����5�ȏ�̈ʒu���
};

