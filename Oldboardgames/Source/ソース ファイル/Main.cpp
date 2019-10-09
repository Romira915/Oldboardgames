#include "DxLib.h"
#include "SceneManager.h"
#include "Task.h"
#include <string>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (ChangeWindowMode(true) != DX_CHANGESCREEN_OK || SetMainWindowText("Mancala") == -1
		|| SetGraphMode(SCREEN_SIZEX, SCREEN_SIZEY, 32) == -1 || SetDoubleStartValidFlag(TRUE)
		|| SetBackgroundColor(35, 35, 35)
		|| DxLib_Init() == -1
		|| SetDrawScreen(DX_SCREEN_BACK) == -1 || SetWindowSizeChangeEnableFlag(TRUE) == -1
		|| SetAlwaysRunFlag(TRUE) == -1 || SetUseASyncLoadFlag(TRUE) == -1)
	{
		return -1;
	}

	int nowloadingHandle[12];
	for (int i = 0; i < 12; i++)
	{
		nowloadingHandle[i] = LoadGraph((std::string("Assets//NowLoading") + std::to_string(i) + ".png").c_str());
	}
	int gifcounter = 0;
	int counter = 0;
	const int speed = 3;

	SceneManager* sceneMgr = new SceneManager;
	sceneMgr->Initialize();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
	{
		sceneMgr->Update();
		sceneMgr->Draw();
		if (GetASyncLoadNum() > 0)
		{
			DrawRotaGraph2(SCREEN_SIZEX - 400 * SCREEN_SIZEX / STD_SCREENSIZEX, SCREEN_SIZEY - 65 * SCREEN_SIZEX / STD_SCREENSIZEX, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, nowloadingHandle[gifcounter], TRUE, FALSE);
			if (counter > speed)
			{
				gifcounter = (gifcounter + 1) % 12;
				counter = 0;
			}
			counter++;
		}
		if (sceneMgr->IsGameEnd())
		{
			break;
		}
	}

	sceneMgr->Finalize();
	delete sceneMgr;

	DxLib_End();				// ＤＸライブラリ使用の終了処理
	return 0;				// ソフトの終了 
}