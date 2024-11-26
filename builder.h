#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void init_builder(int builder_id, int read_fd, int write_fd);
void send_results_to_root(void* word_count_map, int write_fd);