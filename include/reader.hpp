#pragma once
#include "packet.hpp"
#include "result.hpp"
#include <cstddef>
#include <fstream>
#include <inttypes.h>
#include <iostream>
#include <string>
#include <vector>

namespace IO {
class Reader {
public:
  Packet readfile(size_t length) {
    result = FTPResult::FileResult::reading;

    if (currentpos + length >= fileSize) {
      result = FTPResult::FileResult::readOver;
      length = fileSize - currentpos;
    }
    inputFile.seekg(currentpos, std::ios::beg);

    data.resize(length);

    inputFile.read(data.data(), length);

    if (inputFile.fail()) {
      std::cerr << "读取文件失败" << std::endl;
    }
    currentpos += length;
    return Packet(data.data(), length);
  }
  Reader(const std::string &filePath) {
    result = FTPResult::FileResult::waitForRead;
    inputFile.open(filePath, std::ios::binary | std::ios::ate);

    if (!inputFile.is_open()) {
      std::cerr << "无法打开文件 " << filePath << std::endl;
    }

    fileSize = inputFile.tellg();
  }
  ~Reader() {
    if (inputFile.is_open()) {
      inputFile.close();
      result = FTPResult::FileResult::over;
    }
  }

  std::vector<char> data;
  std::ifstream inputFile;
  size_t currentpos = 0;
  std::streamsize fileSize;
  FTPResult::FileResult result = FTPResult::FileResult::waitForRead;
};

} // namespace IO