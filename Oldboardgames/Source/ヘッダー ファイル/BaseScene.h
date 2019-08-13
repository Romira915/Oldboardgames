#pragma once
#include "Task.h"
#include "ISceneChanger.h"
#include "OtherInterface.h"

//�V�[���̊��N���X�B
class BaseScene : public Task {

protected:
	ISceneChanger* mSceneChanger;    //�N���X���L���ɃV�[���؂�ւ���`����C���^�[�t�F�C�X
	OtherInterface* mOtherInterface;

public:
	BaseScene(ISceneChanger* changer);
	BaseScene(ISceneChanger* changer, OtherInterface* OI);
	virtual ~BaseScene() {}
	virtual void Initialize() override {}    //�������������I�[�o�[���C�h�B
	virtual void Finalize() override;        //�I���������I�[�o�[���C�h�B
	virtual void Update() override {}        //�X�V�������I�[�o�[���C�h�B
	virtual void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

};


