#pragma once

#define SCREEN_SIZEX 1280
#define SCREEN_SIZEY 720

#define STD_SCREENSIZEX 1920.0 // ��̃O���t�B�b�N�T�C�Y��
#define STD_SCREENSIZEY 1080.0 // ��̃O���t�B�b�N�T�C�Y����

class Task
{
public:
	virtual ~Task() {}
	virtual void Initialize() {}     //�����������͎������Ă����Ȃ��Ă�����
	virtual void Finalize() {}     //�I�������͎������Ă����Ȃ��Ă�����
	virtual void Update() = 0;   //�X�V�����͕K���p����Ŏ�������
	virtual void Draw() = 0;   //�`�揈���͕K���p����Ŏ�������

private:

};