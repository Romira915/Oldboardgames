#include "SceneManager.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "Title.h"

SceneManager::SceneManager() :
	mNextScene(eScene_None) //���̃V�[���Ǘ��ϐ�
{
	mScene = (BaseScene*) new Title(this);
}

//������
void SceneManager::Initialize() {
	mScene->Initialize();
}

//�I������
void SceneManager::Finalize() {
	mScene->Finalize();
}

//�X�V
void SceneManager::Update() {
	if (mNextScene != eScene_None) {    //���̃V�[�����Z�b�g����Ă�����
		mScene->Finalize();//���݂̃V�[���̏I�����������s
		delete mScene;
		switch (mNextScene) {       //�V�[���ɂ���ď����𕪊�
		case eScene_Title:        //���̉�ʂ����j���[�Ȃ�
			mScene = (BaseScene*) new Title(this);   //���j���[��ʂ̃C���X�^���X�𐶐�����
			break;//�ȉ���
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
