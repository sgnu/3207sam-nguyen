#include "disk.hpp"

// Is the virtual disk open (active)
static bool isActive = false;
// File handle to virtual disk
static int handle;
