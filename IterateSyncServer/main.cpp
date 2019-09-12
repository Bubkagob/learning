#include <atomic>
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <thread>

using namespace boost;

class Service {
 public:
    Service(){}
  void handle_client(asio::ip::tcp::socket &sock) {
    try {

         // read req
      asio::streambuf request;
      asio::read_until(sock, request, "\n");

      // simulate processing
      int i{0};
      while (i != 1000000) i++;
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      // Send response
      std::string response = "Response\n";
      asio::write(sock, asio::buffer(response));

    } catch (system::system_error &se) {
      std::cout << "System error raised! With code: " << se.code()
                << ". Message: " << se.what();
    }
  }
};


class Acceptor{
public:
    Acceptor(asio::io_service& ios, unsigned short port_num): m_ios(ios), m_acceptor(m_ios, asio::ip::tcp::endpoint(asio::ip::address_v4::any(), port_num))
    {
        m_acceptor.listen();
    }

    void accept(){
        asio::ip::tcp::socket socket(m_ios);
        m_acceptor.accept(socket);
        Service service;
        service.handle_client(socket);
    }

private:
    asio::io_service &m_ios;
    asio::ip::tcp::acceptor m_acceptor;
};

class Server{
public:
    Server() : m_stop(false){}

    void start(unsigned short port_num) {
        m_thread.reset(new std::thread([this, port_num](){
            runme(port_num);
        }));
    }

    void stop(){
        m_stop.store(true);
        m_thread->join();
    }

private:
    void runme(unsigned short port_num){
        Acceptor acc (m_ios, port_num);
        while(!m_stop.load()){
            acc.accept();
        }

    }

    std::unique_ptr<std::thread> m_thread;
    std::atomic<bool> m_stop;
    asio::io_service m_ios;
};

int main() {

    unsigned short port_num{3333};
    try {
        Server server;
        server.start(port_num);

        std::this_thread::sleep_for(std::chrono::seconds(50));
        server.stop();



    } catch (system::system_error &se) {
        std::cout << "System error raised! Code: " << se.code() << ". Message: " << se.what();
    }
    return 0; }
