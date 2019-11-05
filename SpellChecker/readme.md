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

## Testing

### networktest.c

A simple echo server; a client connects to the server and any message the client sends is sent back to it.

### intQTest.c

A test to show that the queue works as expeted.

### threadtest.c

A multi-threading test that uses a mutex and condition variables to create a consumer-producer scenario:

There is a single producer (which produces instantly) and multiple consumers (which consume every once in a while). The mutex and condition variables prevent shared resources from
being used simultaneously.

### dicttest.c

A local version of spell checker (it does not host a server). The user can input words and will be told if it is or is not spelled correctly.
