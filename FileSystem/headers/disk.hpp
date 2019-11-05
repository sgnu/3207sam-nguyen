#ifndef DISK_H
#define DISK_H

#define DISK_BLOCKS 16384
#define BLOCK_SIZE  4096

/**
 * Creates an empty, virtual disk file
 */
int makeDisk(string name);

/**
 * Opens a virtual disk (file)
 */
int openDisk(string name);

/**
 * Closes a previously opened disk (file)
 */
int close_disk();

/**
 * Writes a block of size BLOCK_SIZE to disk
 */
int block_write(int block, string buffer);

/**
 * Reads a block of size BLOCK_SIZE from disk
 */
int block_read(int block, string buffer);

#endif
