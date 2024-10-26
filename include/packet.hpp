#pragma once
#include <cstring>
class Packet {
  friend class Session;

public:
  Packet(char *msg, int max_len) {
    data_ = new char[max_len];
    mempcpy(data_, msg, max_len);
  }
  ~Packet() { delete[] data_; }

private:
  int cur_len_;
  int max_len_;
  char *data_;
};