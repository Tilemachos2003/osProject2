#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

void process_text_chunk(FILE* file, const char* exclusion_list, int num_builders, int* pipes);
void hash_and_send_words(const char* word, int num_builders, int* pipes);
void init_splitter(const char* input_file, const char* exclusion_list, int num_builders);