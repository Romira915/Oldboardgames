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

	void Initialize() override;    //�������������I�[�o�[���C�h�B
	void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

private:
	const char* board_filepath = "Assets//manncalaboard.png";
	const std::string coin_filepath = "Assets//coin";
	int boardHandle;
	std::vector<int> coinHandle;
};