#include <boost/asio.hpp>
#include <iostream>

using namespace boost;

struct Session {
  std::shared_ptr<asio::ip::tcp::socket> sock;
  std::unique_ptr<char[]> buf;
  unsigned int buff_size;
};

void callback(const system::error_code& ec, std::size_t bytes_transferred,
              std::shared_ptr<Session> s) {
  if (ec) {
    std::cout << "Error occured! Error code: " << ec.value()
              << ". Message: " << ec.message();
    return;
  }
}

void readFromSocket(std::shared_ptr<asio::ip::tcp::socket> sock) {
  std::shared_ptr<Session> s(new Session);
  const unsigned int MESSAGE_SIZE = 7;
  s->buf.reset(new char[MESSAGE_SIZE]);

  s->sock = sock;
  s->buff_size = MESSAGE_SIZE;

  s->sock->async_read_some(
      asio::buffer(s->buf.get(), s->buff_size),
      std::bind(callback, std::placeholders::_1, std::placeholders::_2, s));
}

int main() {
  std::string raw_ip_address = "127.0.0.1";
  unsigned short port_num = 3333;

  try {
    asio::io_service ios;
    asio::ip::tcp::endpoint ep(asio::ip::tcp::v4(), port_num);

    std::shared_ptr<asio::ip::tcp::socket> socket(
        new asio::ip::tcp::socket(ios, ep.protocol()));

    asio::ip::tcp::acceptor acceptor_(ios, ep);

    socket->connect(ep);
    // acceptor_.accept(*socket);
    readFromSocket(socket);

    ios.run();

  } catch (system::system_error& se) {
    std::cout << "System error raised with code: " << se.code()
              << ". With message:" << se.what();
    return se.code().value();
  }

  return 0;
}
