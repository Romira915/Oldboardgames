#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (ChangeWindowMode(true) != DX_CHANGESCREEN_OK || SetMainWindowText("Mancara") == -1
		|| SetGraphMode(1280, 720, 32) == -1 || DxLib_Init() == -1
		|| SetDrawScreen(DX_SCREEN_BACK) == -1) {
		return -1;
	}

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{

	}



	DxLib_End();				// �c�w���C�u�����g�p�̏I������
	return 0;				// �\�t�g�̏I�� 
}