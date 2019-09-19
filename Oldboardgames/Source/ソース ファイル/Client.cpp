#include "Client.h"

Client::Client(asio::io_service& io_service) : io_service_(io_service), socket_(io_service)
{
}

void Client::Initialize()
{
}

void Client::Finalize()
{
}

void Client::Update()
{
}

void Client::Draw()
{
}

void Client::start()
{
	connect();
}

void Client::connect()
{
	socket_.async_connect(
		tcp::endpoint(asio::ip::address::from_string("192.168.15.2"), 31400),
		boost::bind(&Client::on_connect, this, asio::placeholders::error));
}

void Client::on_connect(const boost::system::error_code& error)
{
	if (error) {
		return;
	}

	send();
}

void Client::send()
{
	send_data_ = "ping";
	asio::async_write(
		socket_,
		asio::buffer(send_data_),
		boost::bind(&Client::on_send, this,
			asio::placeholders::error,
			asio::placeholders::bytes_transferred));
}

void Client::on_send(const boost::system::error_code& error, size_t bytes_transferred)
{
}
