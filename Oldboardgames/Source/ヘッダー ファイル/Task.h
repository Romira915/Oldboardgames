#pragma once

// �E�C���h�E�T�C�Y�ݒ�
#define SCREEN_SIZEX 1280
#define SCREEN_SIZEY 720

#define STD_SCREENSIZEX 1920.0 // ��̃O���t�B�b�N�T�C�Y��
#define STD_SCREENSIZEY 1080.0 // ��̃O���t�B�b�N�T�C�Y����

// �}���J��PvP�V�[���֌W
#define COIN_IMGNUM 5

#define ONEHOLE_COIN 4
#define BOARD_NUM 16
#define COIN_NUM ONEHOLE_COIN * (BOARD_NUM - 2)

#define INIT_SPEED 0.075
#define SPEED 0.03

#define COINFONTSIZE 54 / STD_SCREENSIZEX
// �}���J��PvP�V�[���@�����܂�

// FPS�N���X��`�֌W
#define FPS_FONTSIZE 40 / STD_SCREENSIZEX
// FPS�N���X�@�����܂�

// �^�C�g���V�[���֌W��`
#define PLAYER1_IMGX 0.04
#define PLAYER2_IMGX 0.96
#define PLAYER12_IMGY 0.03

#define TITLE_X 0.5
#define TITLE_Y 0.15
#define PVP_X 0.5
#define PVP_Y 0.45
#define CPU_X 0.5
#define CPU_Y 0.55
#define ONLINE_X 0.5
#define ONLINE_Y 0.65
#define EXIT_X 0.5
#define EXIT_Y 0.75

#define CURSOR_PVP_X (SCREEN_SIZEX * PVP_X - (825 / 2.0 + 97) * SCREEN_SIZEX / STD_SCREENSIZEX)
#define CURSOR_CPU_X (SCREEN_SIZEX * CPU_X - (362 / 2.0 + 97) * SCREEN_SIZEX / STD_SCREENSIZEX)
#define CURSOR_ONLINE_X (SCREEN_SIZEX * ONLINE_X - (329 / 2.0 + 97) * SCREEN_SIZEX / STD_SCREENSIZEX)
#define CURSOR_EXIT_X (SCREEN_SIZEX * EXIT_X - (177 / 2.0 + 97) * SCREEN_SIZEX / STD_SCREENSIZEX)
// �^�C�g���V�[���@�����܂�

// TCP�N���X
#define SERVER_IP "192.168.1.29"
typedef enum {
	eConnected,
	eConnecting,
	eClosed,
	eReceived,
	eReceiving,
	eNone,
} eTCPstatus;
// TCP�N���X�@�����܂�

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