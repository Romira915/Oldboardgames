#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Task.h"

namespace asio = boost::asio;
using asio::ip::tcp;

class Client : public Task {

public:
	Client(asio::io_service& io_service);

	void Initialize();     //初期化処理は実装してもしなくてもいい
	void Finalize();     //終了処理は実装してもしなくてもいい
	void Update();   //更新処理は必ず継承先で実装する
	void Draw();   //描画処理は必ず継承先で実装する

	void start();

private:
	// 接続
	void connect();
	// 接続完了
	void on_connect(const boost::system::error_code& error);
	// メッセージ送信
	void send();
	// 送信完了
	// error : エラー情報
	// bytes_transferred : 送信したバイト数
	void on_send(const boost::system::error_code& error, size_t bytes_transferred);

	asio::io_service& io_service_;
	tcp::socket socket_;
	std::string send_data_; // 送信データ
};