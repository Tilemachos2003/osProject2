#include "utils.h"

// Create a simple pipe
int create_pipe(int fds[2]) {
    if (pipe(fds) == -1) {
        perror("Failed to create pipe");
        exit(EXIT_FAILURE);
    }
    return 0;
}

// Create a named pipe (FIFO)
int create_named_pipe(const char* pipe_name) {
    if (mkfifo(pipe_name, 0666) == -1) {
        perror("Failed to create named pipe");
        exit(EXIT_FAILURE);
    }
    return 0;
}

// Write to a pipe
int write_to_pipe(int fd, const void* buffer, size_t size) {
    if (write(fd, buffer, size) == -1) {
        perror("Failed to write to pipe");
        return -1;
    }
    return 0;
}

// Read from a pipe
int read_from_pipe(int fd, void* buffer, size_t size) {
    if (read(fd, buffer, size) == -1) {
        perror("Failed to read from pipe");
        return -1;
    }
    return 0;
}