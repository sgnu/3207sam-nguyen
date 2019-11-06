# File System Design

Each block is 4096 bytes. There is a total of 16,384 blocks: 8192 blocks for metadata and 8192 blocks for data.

## Blocks

### Metadata Region

There will 256 inodes (ie. 256 files), each of which will comprise of 256 bytes. This totals to 65,536 bytes, or 16 blocks.

The superblock will use 1 block.

A bitmap of all 8192 data blocks will require 8192 bits, or 1024 bytes. This fits in 1 block.

A bitmap of all 256 inodes will require 256 bits, or 32 bytes. This fits in 1 block.

This leaves the metadata region with 8173 blocks for indirect pointers.

