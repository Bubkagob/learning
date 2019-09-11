#include <boost/asio.hpp>
#include <iostream>

using namespace boost;

struct Session {
  std::shared_ptr<asio::ip::tcp::socket> sock;
  std::string buf;
  std::size_t total_bytes_written;
};
void callback(const system::error_code &ec, std::size_t bytes_transferred,
              std::shared_ptr<Session> s) {
  s->total_bytes_written += bytes_transferred;

  if (s->total_bytes_written == s->buf.length()) {
    return;
  }

  s->sock->async_write_some(
      asio::buffer(s->buf.c_str() + s->total_bytes_written,
                   s->buf.length() - s->total_bytes_written),
      std::bind(callback, std::placeholders::_1, std::placeholders::_2, s));
}

void writeToSocket(std::shared_ptr<asio::ip::tcp::socket> sock) {
  std::shared_ptr<Session> s(new Session);

  // Step 4. Allocating and filling the buffer.
  s->buf = std::string("Hello");
  s->total_bytes_written = 0;
  s->sock = sock;

  // Step 5. Initiating asynchronous write opration.
  s->sock->async_write_some(
      asio::buffer(s->buf),
      std::bind(callback, std::placeholders::_1, std::placeholders::_2, s));
}

int main() {
  std::string raw_ip_address = "127.0.0.1";
  unsigned short port_num = 3333;

  try {
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address),
                               port_num);

    asio::io_service ios;

    // Step 3. Allocating, opening and connecting a socket.
    std::shared_ptr<asio::ip::tcp::socket> sock(
        new asio::ip::tcp::socket(ios, ep.protocol()));

    sock->connect(ep);

    writeToSocket(sock);

    // Step 6.
    ios.run();
  } catch (system::system_error &e) {
    std::cout << "Error occured! Error code = " << e.code()
              << ". Message: " << e.what();

    return e.code().value();
  }

  return 0;
}
