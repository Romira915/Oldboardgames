#pragma once
#include "BaseScene.h"
#include "DxLib.h"

#define TITLE_X 0.5
#define TITLE_Y 0.25
#define PVP_X 0.5
#define PVP_Y 0.6
#define EXIT_X 0.5
#define EXIT_Y 0.75

#define CURSOR_PVP_X SCREEN_SIZEX * PVP_X - (825 / 2.0 - 97 / 2.0)
#define CURSOR_EXIT_X SCREEN_SIZEX * EXIT_X - (177 / 2.0 + 97 / 2.0)

typedef enum {
	ePvP,
	eExit,

	Max
}eSelect;

class Title : public BaseScene
{
public:
	Title(ISceneChanger* changer, OtherInterface* OI);

	void Initialize() override;    //初期化処理をオーバーライド。
	void Finalize() override;        //終了処理をオーバーライド。
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。

private:
	const char* title_filepath = "Assets//Title_image.png";
	const char* pvp_filepath = "Assets//select_PvP.png";
	const char* cursor_filepath = "Assets//cursor.png";
	const char* exit_filepath = "Assets//Exit_image.png";
	int titleHandle, pvpHandle, cursorHandle, exitHandle;

	VECTOR cursorXY;
	eSelect eNowCursor;
};

