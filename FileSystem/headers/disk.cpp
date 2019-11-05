#include "disk.h"
#include "disk.hpp"

int makeDisk(string name) {
  return make_dish(name.c_str());
}

int openDisk(string name) {
  return open_disk(name.c_str());
}

int closeDisk() {
  return close_disk();
}

int blockWrite(int block, string buffer) {
  block_write(block, buffer.c_str());
}

int blockRead(int block, string buffer) {
  block_read(block, buffer.c_str());
}
