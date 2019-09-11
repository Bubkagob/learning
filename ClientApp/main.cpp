#include <boost/asio.hpp>
#include <iostream>

using namespace boost;

void communicate(asio::ip::tcp::socket &sock) {
  const char request_buff[] = {0x48, 0x65, 0x0, 0x6c, 0x6c, 0x6f};
  // sending
  asio::write(sock, asio::buffer(request_buff));

  sock.shutdown(asio::socket_base::shutdown_send);

  asio::streambuf response_buf;
  system::error_code ec;
  asio::read(sock, response_buf);
  std::cout << " ----" << ec.value() << std::endl;
  if (ec == asio::error::eof) {
    std::cout << " EOF. Everything s OK." << std::endl;
  } else {
    std::cout << " ----" << ec.value() << std::endl;
    throw system::system_error(ec);
  }
}

int main() {
  std::string raw_ip_address{"127.0.0.1"};
  unsigned short port_num{3333};
  try {
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address),
                               port_num);

    asio::io_service ios;

    asio::ip::tcp::socket sock(ios, ep.protocol());

    sock.connect(ep);

    communicate(sock);

  } catch (system::system_error &se) {
    std::cout << "System error raised with code: " << se.code()
              << ". Message: " << se.what();

    return se.code().value();
  }
  return 0;
}
