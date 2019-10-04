#pragma once

// ウインドウサイズ設定
#define SCREEN_SIZEX 1280
#define SCREEN_SIZEY 720

#define STD_SCREENSIZEX 1920.0 // 基準のグラフィックサイズ幅
#define STD_SCREENSIZEY 1080.0 // 基準のグラフィックサイズ高さ

// マンカラPvPシーン関係
#define COIN_IMGNUM 5

#define ONEHOLE_COIN 4
#define BOARD_NUM 16
#define COIN_NUM ONEHOLE_COIN * (BOARD_NUM - 2)

#define INIT_SPEED 0.075
#define SPEED 0.03

#define COINFONTSIZE 54 / STD_SCREENSIZEX
// マンカラPvPシーン　ここまで

// FPSクラス定義関係
#define FPS_FONTSIZE 40 / STD_SCREENSIZEX
// FPSクラス　ここまで

// タイトルシーン関係定義
#define PLAYER1_IMGX 0.04
#define PLAYER2_IMGX 0.96
#define PLAYER12_IMGY 0.03

#define TITLE_X 0.5
#define TITLE_Y 0.15
#define PVP_X 0.5
#define PVP_Y 0.45
#define CPU_X 0.5
#define CPU_Y 0.55
#define ONLINE_X 0.5
#define ONLINE_Y 0.65
#define EXIT_X 0.5
#define EXIT_Y 0.75

#define CURSOR_PVP_X (SCREEN_SIZEX * PVP_X - (825 / 2.0 + 97) * SCREEN_SIZEX / STD_SCREENSIZEX)
#define CURSOR_CPU_X (SCREEN_SIZEX * CPU_X - (362 / 2.0 + 97) * SCREEN_SIZEX / STD_SCREENSIZEX)
#define CURSOR_ONLINE_X (SCREEN_SIZEX * ONLINE_X - (329 / 2.0 + 97) * SCREEN_SIZEX / STD_SCREENSIZEX)
#define CURSOR_EXIT_X (SCREEN_SIZEX * EXIT_X - (177 / 2.0 + 97) * SCREEN_SIZEX / STD_SCREENSIZEX)
// タイトルシーン　ここまで

// TCPクラス
#define SERVER_IP "192.168.1.29"
typedef enum {
	eConnected,
	eConnecting,
	eClosed,
	eReceived,
	eReceiving,
	eNone,
} eTCPstatus;
// TCPクラス　ここまで

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