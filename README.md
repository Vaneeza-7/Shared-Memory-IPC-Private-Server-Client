# Shared-Memory-IPC-Private-Server-Client

This repository contains the code for a server-client communication using IPC (Inter-Process Communication) with a private shared memory segment. The server and clients are implemented in C programming language. The server process creates a shared memory segment, writes data to it, and waits for the clients to read and modify the data. The clients read the data, perform some calculations, and update the shared memory with the result.

## Code Files
- `main.c`: This file contains the code for the server and client process. It creates a shared memory segment, writes data to it, forks child processes for clients, and waits for the clients to finish. Then the clients read from shared memory and write their own data to it.
- `sum.c`: It contains the code for the 'exec' process.

## Dependencies
- The code uses the following C libraries:
  - `stdio.h`: For input/output operations
  - `sys/ipc.h`: For inter-process communication using keys
  - `unistd.h`: For fork() and other system calls
  - `sys/wait.h`: For waiting on child processes
  - `stdlib.h`: For standard library functions
  - `sys/shm.h`: For shared memory operations
  - `sys/types.h`: For data types
  - `errno.h`: For error handling

## License
This project is licensed under the [MIT License](LICENSE).
