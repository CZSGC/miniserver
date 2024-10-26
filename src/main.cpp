#include "reader.hpp"
#include <asio.hpp>
int main() {
  IO::Reader reader;
  reader.readfile("/home/chenzushou/project/miniftp/test/test.txt");
}