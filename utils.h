#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int create_pipe(int fds[2]);
int create_named_pipe(const char* pipe_name);
int write_to_pipe(int fd, const void* buffer, size_t size);
int read_from_pipe(int fd, void* buffer, size_t size);