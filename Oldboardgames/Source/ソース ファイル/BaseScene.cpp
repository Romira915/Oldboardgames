#include "BaseScene.h"
#include "DxLib.h"

BaseScene::BaseScene(ISceneChanger* changer)
{
	mSceneChanger = changer;
}

BaseScene::BaseScene(ISceneChanger* changer, OtherInterface* OI)
{
	mSceneChanger = changer;
	mOtherInterface = OI;
}

void BaseScene::Finalize() {
}

void BaseScene::Draw() {
}
