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
		cursorXY.y = SCREEN_SIZEY * (PVP_Y - 0.01); 
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
	DrawRotaGraph2(SCREEN_SIZEX * TITLE_X, SCREEN_SIZEY * TITLE_Y, 1051 / 2, 221 / 2, SCREEN_SIZEX / 1920.0, 0, titleHandle, TRUE, FALSE);
	DrawRotaGraph2(SCREEN_SIZEX * PVP_X, SCREEN_SIZEY * PVP_Y, 825 / 2, 101 / 2, SCREEN_SIZEX / 1920.0 * 1, 0, pvpHandle, TRUE, FALSE);
	DrawRotaGraph2(SCREEN_SIZEX * EXIT_X, SCREEN_SIZEY * EXIT_Y, 177 / 2, 76 / 2, SCREEN_SIZEX / 1920.0, 0, exitHandle, TRUE, FALSE);
	DrawRotaGraph2(int(cursorXY.x), int(cursorXY.y), 97 / 2, 40 / 2, SCREEN_SIZEX / 1920.0 * 1, 0, cursorHandle, TRUE, FALSE);
}
