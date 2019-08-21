#pragma once
#include "BaseScene.h"
#include "DxLib.h"



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

