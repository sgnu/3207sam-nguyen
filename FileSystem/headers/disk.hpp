/**
 * Wrapper functions for the provided disk.h and disk.c libraries
 * Allows for easy conversion from C++ strings to C strings
 */

#ifndef _DISK_HPP_
#define _DISK_HPP_

int makeDisk(string name);
int openDisk(string name);
int closeDisk();

int blockWrite(int block, string buffer);
int blockRead(int block, string buffer);

#endif
