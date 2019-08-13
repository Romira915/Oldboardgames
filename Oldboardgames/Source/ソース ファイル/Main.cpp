#include "DxLib.h"
#include "SceneManager.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (ChangeWindowMode(true) != DX_CHANGESCREEN_OK || SetMainWindowText("Mancara") == -1
		|| SetGraphMode(1280, 720, 32) == -1 || DxLib_Init() == -1
		|| SetDrawScreen(DX_SCREEN_BACK) == -1) {
		return -1;
	}

	SceneManager* sceneMgr = new SceneManager;
	sceneMgr->Initialize();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		sceneMgr->Update();
		sceneMgr->Draw();
	}

	sceneMgr->Finalize();
	delete sceneMgr;

	DxLib_End();				// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}