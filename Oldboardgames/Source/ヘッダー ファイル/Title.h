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

	void Initialize() override;    //�������������I�[�o�[���C�h�B
	void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B

private:
	const char* title_filepath = "Assets//Title_image.png";
	const char* pvp_filepath = "Assets//select_PvP.png";
	const char* cursor_filepath = "Assets//cursor.png";
	const char* exit_filepath = "Assets//Exit_image.png";
	int titleHandle, pvpHandle, cursorHandle, exitHandle;

	VECTOR cursorXY;
	eSelect eNowCursor;
};

