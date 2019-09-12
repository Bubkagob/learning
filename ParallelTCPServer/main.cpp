#include <atomic>
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <thread>
using namespace boost;

class Service {
 public:
  Service() {}

  void start_handling_client(std::shared_ptr<asio::ip::tcp::socket> sock) {
    std::thread th(([this, sock]() { handle_client(sock); }));
    th.detach();
  }

 private:
  void handle_client(std::shared_ptr<asio::ip::tcp::socket> sock) {
    try {
      asio::streambuf request;
      asio::read_until(*sock.get(), request, "\n");

      // emulate processing
      int i{0};
      while (i != 1000000) i++;
      std::this_thread::sleep_for(std::chrono::milliseconds(500));

      // sending a response
      std::string response = "Response\n";
      asio::write(*sock.get(), asio::buffer(response));

    } catch (system::system_error &se) {
      std::cout << "Error occured! Error code: " << se.code()
                << ". Message: " << se.what();
    }

    delete this;
  }
};

class Acceptor {
 public:
  Acceptor(asio::io_service &ios, unsigned short port_num)
      : m_ios(ios),
        m_acceptor(m_ios, asio::ip::tcp::endpoint(asio::ip::address_v4::any(),
                                                  port_num)) {
    m_acceptor.listen();
  }

  void accept() {
    std::shared_ptr<asio::ip::tcp::socket> sock(
        new asio::ip::tcp::socket(m_ios));
    m_acceptor.accept(*sock.get());
    (new Service)->start_handling_client(sock);
  }

 private:
  asio::io_service &m_ios;
  asio::ip::tcp::acceptor m_acceptor;
};

class Server {
 public:
  Server() : m_stop(false) {}

  void start(unsigned short port_num) {
    m_thread.reset(new std::thread([this, port_num]() { run(port_num); }));
  }

  void stop() {
    m_stop.store(true);
    m_thread->join();
  }

 private:
  void run(unsigned short port_num) {
    Acceptor acc(m_ios, port_num);
    while (!m_stop.load()) {
      acc.accept();
    }
  }
  std::unique_ptr<std::thread> m_thread;
  std::atomic<bool> m_stop;
  asio::io_service m_ios;
};

int main() {
  unsigned short port_n{3333};
  try {
    Server srv;
    srv.start(port_n);
    std::this_thread::sleep_for(std::chrono::seconds(60));
    srv.stop();
  } catch (system::system_error &se) {
    std::cout << "Error message raised, code: " << se.code()
              << ". Message: " << se.what();
  }
  return 0;
}
