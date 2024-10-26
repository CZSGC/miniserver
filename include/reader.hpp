#pragma once
#include <cstddef>
#include <fstream>
#include <inttypes.h>
#include <iostream>
#include <string>
#include <vector>

namespace IO {
class Reader {
public:
  void readfile(std::string filePath) {
    std::ifstream inputFile(filePath, std::ios::binary | std::ios::ate);

    if (!inputFile.is_open()) {
      std::cerr << "无法打开文件 " << filePath << std::endl;
    }

    std::streamsize fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    data.resize(fileSize);

    inputFile.read(data.data(), fileSize);

    if (inputFile.fail()) {
      std::cerr << "读取文件失败" << std::endl;
    }

    inputFile.close();
  }
  std::vector<char> data;
  size_t length;
};

} // namespace IO