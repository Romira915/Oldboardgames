#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "Task.h"

namespace asio = boost::asio;
using asio::ip::tcp;

class Client : public Task {

public:
	Client(asio::io_service& io_service);

	void Initialize();     //�����������͎������Ă����Ȃ��Ă�����
	void Finalize();     //�I�������͎������Ă����Ȃ��Ă�����
	void Update();   //�X�V�����͕K���p����Ŏ�������
	void Draw();   //�`�揈���͕K���p����Ŏ�������

	void start();

private:
	// �ڑ�
	void connect();
	// �ڑ�����
	void on_connect(const boost::system::error_code& error);
	// ���b�Z�[�W���M
	void send();
	// ���M����
	// error : �G���[���
	// bytes_transferred : ���M�����o�C�g��
	void on_send(const boost::system::error_code& error, size_t bytes_transferred);

	asio::io_service& io_service_;
	tcp::socket socket_;
	std::string send_data_; // ���M�f�[�^
};