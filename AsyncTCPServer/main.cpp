#include <atomic>
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <thread>

using namespace boost;

class Service {
 public:
  Service(std::shared_ptr<asio::ip::tcp::socket> sock) : m_socket(sock) {}

  void start_handling() {
    asio::async_read_until(*m_socket.get(), m_request, "\n",
                           [this](const boost::system::error_code &ec,
                                  std::size_t bytes_transferred) {
                             on_request_received(ec, bytes_transferred);
                           });
  }

 private:
  void on_request_received(const boost::system::error_code &ec,
                           std::size_t bytes_transferred) {
    if (ec) {
      std::cout << "Error occured! Error code:" << ec.value()
                << ". Message: " << ec.message();
      on_finish();
      return;
    }

    m_response = process_request(m_request);

    // write operation
    asio::async_write(*m_socket.get(), asio::buffer(m_response),
                      [this](const boost::system::error_code &ec,
                             std::size_t bytes_transferred) {
                        on_response_sent(ec, bytes_transferred);
                      });
  }

  void on_response_sent(const boost::system::error_code &ec,
                        std::size_t bytes_transferred) {
    if (ec) {
      std::cout << "Error occured! Error code:" << ec.value()
                << ". Message: " << ec.message();
    }
    on_finish();
  }

  std::string process_request(asio::streambuf &request) {
    std::cout << "Request requested " << std::endl;

    int i{0};
    while (i != 1000000) i++;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    std::string response{"Response\n"};
    return response;
  }

  void on_finish() { delete this; }

  std::shared_ptr<asio::ip::tcp::socket> m_socket;
  std::string m_response;
  asio::streambuf m_request;
};

class Acceptor {
 public:
  Acceptor(asio::io_service &ios, unsigned short port_num)
      : m_ios(ios),
        m_acceptor(m_ios, asio::ip::tcp::endpoint(asio::ip::address_v4::any(),
                                                  port_num)),
        m_isStopped(false) {}

  void start() {
    m_acceptor.listen();
    initAccept();
  }

  void stop() { m_isStopped.store(true); }

 private:
  void initAccept() {
    std::shared_ptr<asio::ip::tcp::socket> socket(
        new asio::ip::tcp::socket(m_ios));
    m_acceptor.async_accept(
        *socket.get(), [this, socket](const boost::system::error_code &ec) {
          onAccept(ec, socket);
        });
  }

  void onAccept(const boost::system::error_code &ec,
                std::shared_ptr<asio::ip::tcp::socket> sock) {
    if (!ec) {
      (new Service(sock))->start_handling();
    } else {
      std::cout << "Error occured! Code: " << ec.value()
                << ". Message: " << ec.message();
    }

    if (!m_isStopped.load()) {
      initAccept();
    } else {
      m_acceptor.close();
    }
  }

  asio::io_service &m_ios;
  asio::ip::tcp::acceptor m_acceptor;
  std::atomic<bool> m_isStopped;
};

class Server {
 public:
  Server() { m_work.reset(new asio::io_service::work(m_ios)); }

  void start(unsigned short port_num, unsigned int thread_pool_size) {
    assert(thread_pool_size > 0);

    m_acc.reset(new Acceptor(m_ios, port_num));
    m_acc->start();
    for (unsigned int i{0}; i < thread_pool_size; i++) {
      std::unique_ptr<std::thread> th(
          new std::thread([this]() { m_ios.run(); }));
      m_thread_pool.push_back(std::move(th));
    }
  }

  void stop() {
    m_acc->stop();
    m_ios.stop();
    for (auto &t : m_thread_pool) {
      t->join();
    }
  }

 private:
  asio::io_service m_ios;
  std::unique_ptr<asio::io_service::work> m_work;
  std::unique_ptr<Acceptor> m_acc;
  std::vector<std::unique_ptr<std::thread>> m_thread_pool;
};

const int DEFAULT_THREAD_POOL_SIZE{2};

int main() {
  const unsigned short port_num{3333};
  try {
    Server server;
    unsigned int thread_pool_size{std::thread::hardware_concurrency() * 2};
    if (thread_pool_size == 0) thread_pool_size = DEFAULT_THREAD_POOL_SIZE;

    server.start(port_num, thread_pool_size);
    std::this_thread::sleep_for(std::chrono::seconds(6));
    server.stop();

  } catch (system::system_error &se) {
    std::cout << "Error occured! Code: " << se.code()
              << ". Message: " << se.what();
  }

  return 0;
}
