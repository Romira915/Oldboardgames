#pragma once
typedef enum {
	eScene_Title,    //�^�C�g�����
	eScene_MancalaPvP,    //�Q�[�����
	eScene_MancalaOnline, //�I�����C���ΐ���

	eScene_End,		//�Q�[���I��

	eScene_None,    //����
} eScene;

//�V�[����ύX���邽�߂̃C���^�[�t�F�C�X�N���X
class ISceneChanger {
public:
	virtual ~ISceneChanger() {}
	virtual void ChangeScene(eScene NextScene) = 0;	//�w��V�[���ɕύX����
};