#include "disk.h"
#include "wrapper.hpp"

using namespace std;

int makeDisk(string name) {
  return make_disk((char *) name.c_str());
}

int openDisk(string name) {
  return open_disk((char *) name.c_str());
}

int closeDisk() {
  return close_disk();
}

int blockWrite(int block, string buffer) {
  block_write(block, (char *) buffer.c_str());
}

int blockRead(int block, string buffer) {
  block_read(block, (char *) buffer.c_str());
}
