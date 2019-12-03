# File System Design

Each block is 4096 bytes. There is a total of 16,384 blocks and will be split evenly between the metadata and data regions: 8192 blocks for metadata and 8192 blocks for data.

## Metadata Region: Block Allocation

There will 256 inodes (ie. 256 files), each of which will comprise of 256 bytes. This totals to 65,536 bytes, or 16 blocks; however, each inode will have its own block to make the
file system's design simpler. This means 256 blocks will be used.

The superblock will use 1 block.

A bitmap of all 256 inodes will require 256 bits, or 32 bytes. This fits in 1 block.

A bitmap of all 8192 data blocks will require 8192 bits, or 1024 bytes. This fits in 1 block.

This leaves the metadata region with 7,933 blocks for indirect pointers. There is enough space for each inode to use an entire block for pointers.

This means a total of 515 blocks will be used.

## Inodes

Each inode will need to have:

1. Name
2. Type
3. Size
4. Number of blocks
5. Time
6. Date
7. Pointer to pointer block [the i-th inode should point to the i-th pointer block]

If it is a directory, its data block should contain information about its children (maybe indexes of inodes?).

```cpp
struct inode {
  char[16] name;
  bool isDir;
  uint32 size;
  uint32 blocks;
  // Time
  // Date
  uint32 pointerBlock;
}
```

## Superblock

Stuff goes here

## Pseudocode

### Macros

These are global macros for easy reference to superblock, inodes, and data.

```cpp
#define SUPERBLOCK 0
#define INODE_BITMAP 1
#define DATA_BITMAP 2
```

### Wrapper

Wrapper header and source files are included for easy use with C++'s string instead of C's char \*. Additionally, methods for converting structs into strings and strings into structs (such as for inode structs) needs to be implemented.

### makeFS

```cpp
int makeFS(string diskName) {
  if (makeDisk(diskName) != 0)
    return -1;

  if (openDisk(diskName) != 0)
    return -1;

  // Write to superblock
  if (blockWrite(SUPERBLOCK, initial_superblock_information) != 0)
    return -1;

  // Write inode bitmap
  // The first inode should be the root dir
  if (blockWrite(INODE_BITMAP, initial_inode_bitmap) != 0) // INODE_BITMAP should be a single 1 followed by all 0s
    return -1;

  // Write data bitmap
  if (blockWrite(DATA_BITMAP, initial_data_bitmap) != 0)  // DATA_BITMAP should a single 1 followed by all 0s
    return -1;

  // Write root dir
  if (blockWrite(getPointerBlock(0), root_dir_information) != 0)
    return -1;

  return closeDisk(); // Returns 0 on success or -1 on failure
}
```

### mountFS

```cpp
int mountFS(string diskName) {
  if (openDisk(diskName) != 0)
    return -1;

  /* Fill inode bitmap
   *    Read through the string acquired by readBlock()
   *    A global array of bool inodeBitmap will be filled by going through the string char by char
   */

  /* Fill data bitmap
   *    Same as inode bitmap but with the data bitmap
   *    A method for reading bitmaps into an array/vector may be created
   */
}
```

### unmountFS

```cpp
int unmountFS(string diskName) {
  /*
   * Convert structures to strings and write them to the filesystem
   * ie.
   * Convert inode bitmap to a (binary) string and store it in the inode block (using blockWrite())
   */

  return closeDisk(); // Returns 0 on success or -1 on failure
}
```

### fsOpen

```cpp
// A global map of int to int
// Key: the file descriptor
// Value: the inode

map<int, int> globalMap;

int fsOpen(string name) {
  if (globalMap.size >= 64) {
    cerr << "Too many file descriptors" << endl;
    return -1;
  }

  // Use inode bitmap to check which inodes exist and attempt to find one with the name
  if (fileNotFound) {
    cerr << "File could not be found" << endl;
    return -1;
  }

  globalMap.add(pair(newFD, inode));
}
```

### fsClose

```cpp
int fsClose(int fileDescriptor) {
  if (globalMap.contains(fileDescriptor)) {
    globalMap.remove(fileDescriptor);
    return 0;
  } else {
    cerr << "File descriptor " << fileDescriptor << " does not exist" << endl;
    return -1;
  }
}
```

### fsCreate

```cpp
int fsCreate(string name) {
  // Check inode bitmap if there is an available inode

  // Use inode bitmap to check which inodes exist and if the filename already exists
  if (fileIsFound) {
    cerr << name << " already exists" << endl;
    return -1;
  }

  /*
   * Fill in a bit on the inode bitmap
   * Initialize inode information in the inode block
   */
}
```

### fsDelete

```cpp
int fsDelete(string name) {
  // Check if file exists
  if (fileNotFound) {
    cerr << name << " does not exist" << endl;
    return -1;
  }

  /*
   * Fill in the corresponding bit in the inode bitmap as 0
   */
}
```

### makeDir

```cpp
int makeDir(string name) {
  // Create a new file
  fsCreate(name);

  // Set new file as dir
  setIsDir(name, true);
}
```

### fsRead

```cpp
int fsRead(int fileDescriptor, string buffer, size_t nBytes) {
  buffer = "";
  int count = 0;

  while (notEOF(fileDescriptor) && count < nBytes) {
    count ++;
    buffer += charAt(fileDescriptor);
    moveForward(fileDescriptor);
  }

  return count;
}
```

### fsWrite

```cpp
int fsWrite(int fileDescriptor, string buffer, size_t nBytes) {

}
```

