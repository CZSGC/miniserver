#pragma once
#include "packet.hpp"
#include "reader.hpp"
#include <asio.hpp>
#include <queue>

class Session : public std::enable_shared_from_this<Session> {
public:
  typedef std::shared_ptr<Session> pointer;

  asio::ip::tcp::socket &socket() { return socket_; }

  void start();

  static pointer create(asio::io_context &io_context) {
    return pointer(new Session(io_context));
  }
  void Send(char *msg, int max_length);
  Session(
      asio::io_context &io_context,
      std::string filePath = "/home/chenzushou/project/miniftp/test/test.txt");

private:
  void handleRead(const std::error_code &error, size_t bytes_transferred,
                  std::shared_ptr<Session> selfShared);
  void handleWrite(const std::error_code &error,
                   std::shared_ptr<Session> selfShared);

  enum { maxLength = 1024 };
  char data_[maxLength];

  asio::ip::tcp::socket socket_;
  std::string message_;
  std::mutex send_lock_;
  std::queue<std::shared_ptr<Packet>> send_que_;
  IO::Reader reader;
};