#include "Title.h"
#include "DxLib.h"

Title::Title(ISceneChanger* changer, OtherInterface* OI) : BaseScene(changer, OI)
{
}

void Title::Initialize()
{
	titleHandle = LoadGraph(title_filepath);
	pvpHandle = LoadGraph(pvp_filepath);
	cpuHandle = LoadGraph(cpu_filepath);
	onlineHandle = LoadGraph(Online_filepath);
	cursorHandle = LoadGraph(cursor_filepath);
	exitHandle = LoadGraph(exit_filepath);

	eNowCursor = ePvP;
	cursorXY.x = CURSOR_PVP_X;
	cursorXY.y = SCREEN_SIZEY * (PVP_Y - 0.01);
}

void Title::Finalize()
{
	DeleteGraph(titleHandle);
	DeleteGraph(pvpHandle);
	DeleteGraph(cpuHandle);
	DeleteGraph(onlineHandle);
	DeleteGraph(cursorHandle);
	DeleteGraph(exitHandle);
}

void Title::Update()
{
	if (mOtherInterface->KeyDown(KEY_INPUT_DOWN))
	{
		eNowCursor = eMancalaMode((eNowCursor + 1) % Max);
	}
	if (mOtherInterface->KeyDown(KEY_INPUT_UP))
	{
		eNowCursor = eMancalaMode((eNowCursor - 1 + Max) % Max);
	}

	switch (eNowCursor)
	{
	case ePvP:
		cursorXY.x = CURSOR_PVP_X;
		cursorXY.y = SCREEN_SIZEY * (PVP_Y + 0.015);
		if (mOtherInterface->KeyDown(KEY_INPUT_RETURN))
		{
			mSceneChanger->ChangeScene(eScene_MancalaPvP);
		}
		break;
	case eCPU:
		cursorXY.x = CURSOR_CPU_X;
		cursorXY.y = SCREEN_SIZEY * (CPU_Y + 0.025);
		if (mOtherInterface->KeyDown(KEY_INPUT_RETURN))
		{
			mSceneChanger->ChangeScene(eScene_MancalaCPU);
		}
		break;
	case eOnline:
		cursorXY.x = CURSOR_ONLINE_X;
		cursorXY.y = SCREEN_SIZEY * (ONLINE_Y + 0.016);
		if (mOtherInterface->KeyDown(KEY_INPUT_RETURN))
		{
			mSceneChanger->ChangeScene(eScene_MancalaOnline);
		}
		break;
	case eExit:
		cursorXY.x = CURSOR_EXIT_X;
		cursorXY.y = SCREEN_SIZEY * (EXIT_Y + 0.015);
		if (mOtherInterface->KeyDown(KEY_INPUT_RETURN))
		{
			mSceneChanger->ChangeScene(eScene_End);
		}
		break;
	default:
		break;
	}
}

void Title::Draw()
{
	DrawRotaGraph2(SCREEN_SIZEX * TITLE_X - (1051.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX), SCREEN_SIZEY * TITLE_Y, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, titleHandle, TRUE, FALSE);
	DrawRotaGraph2(SCREEN_SIZEX * PVP_X - (825.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX), SCREEN_SIZEY * PVP_Y, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, pvpHandle, TRUE, FALSE);
	DrawRotaGraph2(SCREEN_SIZEX * CPU_X - (362.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX), SCREEN_SIZEY * CPU_Y, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, cpuHandle, TRUE, FALSE);
	DrawRotaGraph2(SCREEN_SIZEX * ONLINE_X - (329.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX), SCREEN_SIZEY * ONLINE_Y, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, onlineHandle, TRUE, FALSE);
	DrawRotaGraph2(SCREEN_SIZEX * EXIT_X - (177.0 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX), SCREEN_SIZEY * EXIT_Y, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, exitHandle, TRUE, FALSE);
	DrawRotaGraph2(cursorXY.x, cursorXY.y, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, cursorHandle, TRUE, FALSE);
}
