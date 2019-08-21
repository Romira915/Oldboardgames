#include "SceneManager.h"
#include "DxLib.h"
#include "Title.h"
#include "Mancala.h"

SceneManager::SceneManager() :
	mNextScene(eScene_None) //次のシーン管理変数
	, fps(60, 60)
{
	mOther = new Other();
	mScene = (BaseScene*) new Title(this, mOther);
}

//初期化
void SceneManager::Initialize() {
	isGameEnd = false;
	mOther->Initialize();
	mScene->Initialize();
	fps.Initialize();
}

//終了処理
void SceneManager::Finalize() {
	mOther->Finalize();
	delete mOther;
	mScene->Finalize();
	fps.Finalize();
}

//更新
void SceneManager::Update() {
	mOther->Update();
	fps.Update();
	if (mNextScene != eScene_None) {    //次のシーンがセットされていたら
		mScene->Finalize();//現在のシーンの終了処理を実行
		delete mScene;
		switch (mNextScene) {       //シーンによって処理を分岐
		case eScene_Title:        //次の画面がメニューなら
			mScene = (BaseScene*) new Title(this, mOther);   //メニュー画面のインスタンスを生成する
			break;//以下略
		case eScene_MancalaPvP:
			mScene = (BaseScene*) new Mancala(this, mOther);
			break;
		case eScene_End:
			isGameEnd = true;
			mScene = new BaseScene(this, mOther); // ダミーのScene
			break;
		}
		mNextScene = eScene_None;    //次のシーン情報をクリア
		mScene->Initialize();    //シーンを初期化
	}

	mScene->Update(); //シーンの更新
	fps.Wait();
}

//描画
void SceneManager::Draw() {
	fps.Draw();
	mScene->Draw(); //シーンの描画
}

// 引数 NextScene にシーンを変更する
void SceneManager::ChangeScene(eScene NextScene) {
	mNextScene = NextScene;    //次のシーンをセットする
}

bool SceneManager::IsGameEnd() const
{
	return isGameEnd;
}
