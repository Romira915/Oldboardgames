#include "SceneManager.h"
#include "DxLib.h"
#include "Title.h"
#include "Mancala.h"

SceneManager::SceneManager() :
	mNextScene(eScene_None) //���̃V�[���Ǘ��ϐ�
{
	mOther = new Other();
	mScene = (BaseScene*) new Title(this,mOther);
}

//������
void SceneManager::Initialize() {
	isGameEnd = false;
	mOther->Initialize();
	mScene->Initialize();
}

//�I������
void SceneManager::Finalize() {
	mOther->Finalize();
	delete mOther;
	mScene->Finalize();
}

//�X�V
void SceneManager::Update() {
	mOther->Update();
	if (mNextScene != eScene_None) {    //���̃V�[�����Z�b�g����Ă�����
		mScene->Finalize();//���݂̃V�[���̏I�����������s
		delete mScene;
		switch (mNextScene) {       //�V�[���ɂ���ď����𕪊�
		case eScene_Title:        //���̉�ʂ����j���[�Ȃ�
			mScene = (BaseScene*) new Title(this, mOther);   //���j���[��ʂ̃C���X�^���X�𐶐�����
			break;//�ȉ���
		case eScene_Game:
			mScene = (BaseScene*) new Mancala(this, mOther);
			break;
		case eScene_End:
			isGameEnd = true;
			mScene = new BaseScene(this, mOther); // �_�~�[��Scene
			break;
		}
		mNextScene = eScene_None;    //���̃V�[�������N���A
		mScene->Initialize();    //�V�[����������
	}

	mScene->Update(); //�V�[���̍X�V
}

//�`��
void SceneManager::Draw() {
	mScene->Draw(); //�V�[���̕`��
}

// ���� NextScene �ɃV�[����ύX����
void SceneManager::ChangeScene(eScene NextScene) {
	mNextScene = NextScene;    //���̃V�[�����Z�b�g����
}

bool SceneManager::IsGameEnd() const
{
	return isGameEnd;
}
