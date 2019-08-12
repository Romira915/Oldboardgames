#include "BaseScene.h"
#include "BaseScene.h"
#include "DxLib.h"

BaseScene::BaseScene(ISceneChanger* changer)
{
	mSceneChanger = changer;
}

void BaseScene::Finalize() {
}

void BaseScene::Draw() {
}
