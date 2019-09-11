#include <atomic>
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <thread>

using namespace boost;

class Service {
 public:
  Service();
  void handle_client(asio::ip::tcp::socket &sock) {
    try {
      asio::streambuf request;
      asio::read_until(sock, request, "\n");

      int i{0};
      while (i != 1000000) i++;
      std::this_thread::sleep_for(std::chrono::milliseconds(500));

      std::string response = "Response\n";
      asio::write(sock, asio::buffer(response));

    } catch (system::system_error &se) {
      std::cout << "System error raised! With code: " << se.code()
                << ". Message: " << se.what();
    }
  }
};

int main() { return 0; }
