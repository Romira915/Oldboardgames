#pragma once
#include "ISceneChanger.h"
#include "BaseScene.h"
#include "Other.h"
#include "FPS.h"

class SceneManager : public ISceneChanger, Task {

private:
	BaseScene* mScene;    //�V�[���Ǘ��ϐ�
	eScene mNextScene;    //���̃V�[���Ǘ��ϐ�
	Other* mOther;
	FPS fps;

	bool isGameEnd;
public:
	SceneManager();
	void Initialize() override;	//������
	void Finalize() override;	//�I������
	void Update() override;		//�X�V
	void Draw() override;		//�`��

	// ���� NextScene �ɃV�[����ύX����
	void ChangeScene(eScene NextScene) override;

	bool IsGameEnd() const;
};