#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void parse_arguments(int argc, char* argv[], char** input_file, int* num_splitters, 
                     int* num_builders, int* top_k, char** exclusion_list, char** output_file);
void signal_handler(int signo);
void create_splitters(int num_splitters, const char* input_file, const char* exclusion_list);
void create_builders(int num_builders);
void collect_results(int top_k, const char* output_file);