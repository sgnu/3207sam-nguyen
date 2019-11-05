# Networked Spell Checker

This is an application that uses sockets to spell check words. Additionally, the server is multi-thread allowing for multiple concurrent clients to be connected and getting spell
checks at once.

## Design

The spell checker uses 2 types of threads in addition to the main thread:

1. spellChecker

- Does the actual spell checking

2. logger

- Logs words and if they are correctly spelled to a file

### Modularity

A significant portion of the reusable code is written in header and source files that allow for easy reuse in other projects. The rest of the reusable code is written as functions
inside of the source files (ie. `main.c` or any of the `*test.c`).

### Synchronization

In `main.c`, the shared resources (log queue and fd queue) are synchronized through a mutex and condition variables for empty and full (one of each for each resource).
