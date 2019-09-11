#include <boost/asio.hpp>
#include <iostream>

using namespace boost;

void processRequest(asio::ip::tcp::socket &sock) {
  asio::streambuf request_buf;
  system::error_code ec;
  asio::read(sock, request_buf, ec);
  std::cout << " ----" << ec.message() << std::endl;
  if (ec != asio::error::eof) {
    std::cout << (ec != asio::error::eof) << std::endl;
    throw system::system_error(ec);
  }

  const char response_buf[] = {0x48, 0x69, 0x21};
  asio::write(sock, asio::buffer(response_buf));
  std::cout << " SHUTDOWN server sock" << std::endl;
  sock.shutdown(asio::socket_base::shutdown_send);
}

int main() {
  unsigned short port_num{3333};
  try {
    asio::ip::tcp::endpoint ep(asio::ip::address_v4::any(), port_num);

    asio::io_service ios;
    asio::ip::tcp::acceptor acceptor(ios, ep);

    asio::ip::tcp::socket sock(ios);
    acceptor.accept(sock);
    processRequest(sock);

  } catch (system::system_error &se) {
    std::cout << "System error raised! Code: " << se.code()
              << ". Message: " << se.what() << std::endl;
    return se.code().value();
  }
  return 0;
}
