#pragma once
#include "session.hpp"
#include <asio.hpp>
#include <ctime>
#include <functional>
#include <mutex>

class ConnectManager {
public:
  static ConnectManager *getInstance(asio::io_context &io_context) {
    if (!instance) {

      std::lock_guard<std::mutex> lock(mutex);
      if (!instance) {
        instance = new ConnectManager(io_context);
      }
    }
    return instance;
  }
  static void destroyInstance() {
    delete instance;
    instance = nullptr;
  }

private:
  ConnectManager(asio::io_context &io_context)
      : ioContext_(io_context),
        acceptor_(io_context,
                  asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 3888)) {
    startAccept();
  }

  ConnectManager(const ConnectManager &) = delete;
  ConnectManager &operator=(const ConnectManager &) = delete;

  void startAccept();

  void handleAccept(Session::pointer new_connection,
                    const std::error_code &error);

  static ConnectManager *instance;
  static std::mutex mutex;
  short _port;
  asio::io_context &ioContext_;
  asio::ip::tcp::acceptor acceptor_;
};
