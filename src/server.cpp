#include "server.hpp"
#include "session.hpp"

void ConnectManager::startAccept() {

  Session::pointer new_connection = Session::create(ioContext_);

  acceptor_.async_accept(new_connection->socket(),
                         std::bind(&ConnectManager::handleAccept, this,
                                   new_connection, asio::placeholders::error));
}

void ConnectManager::handleAccept(Session::pointer new_connection,
                                  const std::error_code &error) {
  if (!error) {
    new_connection->start();
  }
  startAccept();
}