#pragma once

#define SCREEN_SIZEX 1280
#define SCREEN_SIZEY 720

#define STD_SCREENSIZEX 1920.0 // 基準のグラフィックサイズ幅
#define STD_SCREENSIZEY 1080.0 // 基準のグラフィックサイズ高さ

class Task
{
public:
	virtual ~Task() {}
	virtual void Initialize() {}     //初期化処理は実装してもしなくてもいい
	virtual void Finalize() {}     //終了処理は実装してもしなくてもいい
	virtual void Update() = 0;   //更新処理は必ず継承先で実装する
	virtual void Draw() = 0;   //描画処理は必ず継承先で実装する

private:

};