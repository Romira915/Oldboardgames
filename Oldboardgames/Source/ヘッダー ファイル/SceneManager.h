#pragma once
#include "ISceneChanger.h"
#include "BaseScene.h"
#include "Other.h"
#include "FPS.h"

class SceneManager : public ISceneChanger, Task {

private:
	BaseScene* mScene;    //シーン管理変数
	eScene mNextScene;    //次のシーン管理変数
	Other* mOther;
	FPS fps;

	bool isGameEnd;
public:
	SceneManager();
	void Initialize() override;	//初期化
	void Finalize() override;	//終了処理
	void Update() override;		//更新
	void Draw() override;		//描画

	// 引数 NextScene にシーンを変更する
	void ChangeScene(eScene NextScene) override;

	bool IsGameEnd() const;
};