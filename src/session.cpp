#include <asio.hpp>
#include <iostream>
#include <packet.hpp>
#include <session.hpp>

void Session::handleRead(const std::error_code &error, size_t bytes_transferred,
                         std::shared_ptr<Session> selfShared) {
  if (!error) {
    std::cout << "read data is " << data_ << std::endl;
    // 发送数据
    Send(data_, bytes_transferred);
    memset(data_, 0, maxLength);
    socket_.async_read_some(asio::buffer(data_, maxLength),
                            std::bind(&Session::handleRead, this,
                                      std::placeholders::_1,
                                      std::placeholders::_2, selfShared));
  } else {
    std::cout << "handle read failed, error is " << error.message()
              << std::endl;
  }
}

void Session::handleWrite(const std::error_code &error,
                          std::shared_ptr<Session> selfShared) {
  if (!error) {
    std::lock_guard<std::mutex> lock(send_lock_);
    send_que_.pop();
    if (!send_que_.empty()) {
      auto &packet = send_que_.front();
      asio::async_write(socket_, asio::buffer(packet->data_, packet->max_len_),
                        std::bind(&Session::handleWrite, this,
                                  std::placeholders::_1, selfShared));
    }
  } else {
    std::cout << "handle write failed, error is " << error.message()
              << std::endl;
  }
}

Session::Session(asio::io_context &ioc) : socket_(ioc) {}

void Session::Send(char *packet, int maxLength) {
  bool pending = false;
  std::lock_guard<std::mutex> lock(send_lock_);
  if (send_que_.size() > 0) {
    pending = true;
  }
  send_que_.push(std::make_shared<Packet>(packet, maxLength));
  if (pending) {
    return;
  }
  asio::async_write(socket_, asio::buffer(packet, maxLength),
                    std::bind(&Session::handleWrite, this,
                              std::placeholders::_1, shared_from_this()));
}