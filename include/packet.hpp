#pragma once
#include <cstring>
class Packet {
  friend class Session;

public:
  Packet(char *msg, int len) {
    data_ = new char[len];
    mempcpy(data_, msg, len);
  }
  ~Packet() { delete[] data_; }

private:
  int len_;
  char *data_;
};