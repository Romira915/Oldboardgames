#include "Title.h"
#include "DxLib.h"

Title::Title(ISceneChanger* changer, OtherInterface* OI) : BaseScene(changer, OI)
{
}

void Title::Initialize()
{
	titleHandle = LoadGraph(title_filepath);
	pvpHandle = LoadGraph(pvp_filepath);
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
	DeleteGraph(cursorHandle);
	DeleteGraph(exitHandle);
}

void Title::Update()
{
	if (mOtherInterface->KeyDown(KEY_INPUT_DOWN))
	{
		eNowCursor = eSelect((eNowCursor + 1) % Max);
	}
	if (mOtherInterface->KeyDown(KEY_INPUT_UP))
	{
		eNowCursor = eSelect((eNowCursor - 1 + Max) % Max);
	}

	switch (eNowCursor)
	{
	case ePvP:
		cursorXY.x = CURSOR_PVP_X;
		cursorXY.y = SCREEN_SIZEY * (PVP_Y - 0.015); 
		if (mOtherInterface->KeyDown(KEY_INPUT_RETURN))
		{
			mSceneChanger->ChangeScene(eScene_Game);
		}
		break;
	case eExit: 
		cursorXY.x = CURSOR_EXIT_X;
		cursorXY.y = SCREEN_SIZEY * EXIT_Y;
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
	DrawRotaGraph2(SCREEN_SIZEX * TITLE_X - (1051 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX), SCREEN_SIZEY * TITLE_Y - 221 / 2, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, titleHandle, TRUE, FALSE);
	DrawRotaGraph2(SCREEN_SIZEX * PVP_X - (825 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX), SCREEN_SIZEY * PVP_Y - 101 / 2, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX * 1, 0, pvpHandle, TRUE, FALSE);
	DrawRotaGraph2(SCREEN_SIZEX * EXIT_X - (177 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX), SCREEN_SIZEY * EXIT_Y - 76 / 2, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX, 0, exitHandle, TRUE, FALSE);
	DrawRotaGraph2(cursorXY.x - (97 / 2 * SCREEN_SIZEX / STD_SCREENSIZEX), cursorXY.y - 40 / 2, 0, 0, SCREEN_SIZEX / STD_SCREENSIZEX * 1, 0, cursorHandle, TRUE, FALSE);
}
