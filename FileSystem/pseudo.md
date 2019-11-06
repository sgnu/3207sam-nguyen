# File System Design

Each block is 4096 bytes. There is a total of 16,384 blocks and will be split evenly between the metadata and data regions: 8192 blocks for metadata and 8192 blocks for data.

## Metadata Region Block Allocation

There will 256 inodes (ie. 256 files), each of which will comprise of 256 bytes. This totals to 65,536 bytes, or 16 blocks.

The superblock will use 1 block.

A bitmap of all 8192 data blocks will require 8192 bits, or 1024 bytes. This fits in 1 block.

A bitmap of all 256 inodes will require 256 bits, or 32 bytes. This fits in 1 block.

This leaves the metadata region with 8173 blocks for indirect pointers. There is enough space for each inode to use an entire block for pointers; however, each pointer block will use only 2 bytes (up to 65,536).

This means a total of 275 blocks will be used.

## Inodes

Each inode will need to have:

1. Name - 16 bytes (15 chars and '\0')
2. Type - 1 bit bool (either file or dir maybe?)
3. Size - 4 bytes (4096 bytes \* 8192 blocks)
4. Number of blocks - 2 bytes (can only be up to 8192 blocks)
5. Protection info
6. Time
7. Pointer to pointer block [the i-th inode should point to the i-th pointer block]

```c++
struct Inode {
  char[16] name;
  bool isDir: 1;
  uint32 size;
}
```
