#include <boost/predef.h>
#ifdef BOOST_OS_WINDOWS
#define _WIN32_WINNT 0x0501
#if _WIN32_WINNT <= 0x0502
#define BOOST_ASIO_DISABLE_IOCP
#define BOOST_ASIO_ENABLE_CANCELIO
#endif
#endif

#include <boost/asio.hpp>
#include <iostream>
#include <thread>

using namespace boost;

int main() {
  std::string raw_ip_address = "127.0.0.1";
  unsigned short port_num{3333};

  try {
    asio::ip::tcp::endpoint ep(asio::ip::address::from_string(raw_ip_address),
                               port_num);
    asio::io_service ios;
    std::shared_ptr<asio::ip::tcp::socket> socket(
        new asio::ip::tcp::socket(ios, ep.protocol()));

    socket->async_connect(ep, [socket](const boost::system::error_code &ec) {
      if (ec) {
        if (ec == asio::error::operation_aborted) {
          std::cout << "Operation cancelled!" << std::endl;
        } else {
          std::cout << "Error occured! Error code = " << ec.value()
                    << ". Message: " << ec.message();
        }
        return;
      }
    });
    std::thread worker_thread([&ios]() {
      try {
        ios.run();
      } catch (system::system_error &ec) {
        std::cout << "Error occured! Code: " << ec.code()
                  << ". Message: " << ec.what();
      }
    });

    // delay

    std::this_thread::sleep_for(std::chrono::seconds(0));
    socket->cancel();

    worker_thread.join();

  } catch (system::system_error &ec) {
    std::cout << "Error occured! Code: " << ec.code()
              << ". Message: " << ec.what();
  }

  return 0;
}
