#include "Title.h"
#include "DxLib.h"

Title::Title(ISceneChanger* changer) : BaseScene(changer)
{
}

void Title::Initialize()
{
	titleHandle = LoadGraph(title_filepath);
	pvpHandle = LoadGraph(pvp_filepath);
	cursorHandle = LoadGraph(cursor_filepath);
	exitHandle = LoadGraph(exit_filepath);

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

}

void Title::Draw()
{
	DrawRotaGraph2(SCREEN_SIZEX * TITLE_X, SCREEN_SIZEY * TITLE_Y, 1051 / 2, 221 / 2, SCREEN_SIZEX / 1920.0, 0, titleHandle, TRUE, FALSE);
	DrawRotaGraph2(SCREEN_SIZEX * PVP_X, SCREEN_SIZEY * PVP_Y, 825 / 2, 101 / 2, SCREEN_SIZEX / 1920.0 * 1, 0, pvpHandle, TRUE, FALSE);
	DrawRotaGraph2(SCREEN_SIZEX * EXIT_X, SCREEN_SIZEY * EXIT_Y, 177 / 2, 76 / 2, SCREEN_SIZEX / 1920.0, 0, exitHandle, TRUE, FALSE);
	DrawRotaGraph2(int(cursorXY.x), int(cursorXY.y), 97 / 2, 40 / 2, SCREEN_SIZEX / 1920.0 * 1, 0, cursorHandle, TRUE, FALSE);
}
