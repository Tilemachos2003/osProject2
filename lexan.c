#include "lexan.h"

// Signal counters
static volatile int usr1_signals = 0;
static volatile int usr2_signals = 0;

// Signal handler
void signal_handler(int signo) {
    if (signo == SIGUSR1) {
        usr1_signals++;
    } else if (signo == SIGUSR2) {
        usr2_signals++;
    }
}

// Parse command-line arguments
void parse_arguments(int argc, char* argv[], char** input_file, int* num_splitters, 
                     int* num_builders, int* top_k, char** exclusion_list, char** output_file) {
    int opt;
    while ((opt = getopt(argc, argv, "i:l:m:t:e:o:")) != -1) {
        switch (opt) {
            case 'i':
                *input_file = optarg;
                break;
            case 'l':
                *num_splitters = atoi(optarg);
                break;
            case 'm':
                *num_builders = atoi(optarg);
                break;
            case 't':
                *top_k = atoi(optarg);
                break;
            case 'e':
                *exclusion_list = optarg;
                break;
            case 'o':
                *output_file = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s -i input_file -l num_splitters -m num_builders -t top_k -e exclusion_list -o output_file\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
}

// Create splitter processes
void create_splitters(int num_splitters, const char* input_file, const char* exclusion_list) {
    for (int i = 0; i < num_splitters; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            execlp("./splitter", input_file, exclusion_list, NULL);
            perror("Failed to exec splitter");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("Failed to fork splitter");
            exit(EXIT_FAILURE);
        }
    }
}

// Create builder processes
void create_builders(int num_builders) {
    for (int i = 0; i < num_builders; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            execlp("./builder", NULL);
            perror("Failed to exec builder");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("Failed to fork builder");
            exit(EXIT_FAILURE);
        }
    }
}

// Collect results from builders
void collect_results(int top_k, const char* output_file) {
    // Placeholder for merging results logic
    printf("Collecting results and writing top-%d words to %s\n", top_k, output_file);
}

// Main function
int main(int argc, char* argv[]) {
    char* input_file = NULL;
    char* exclusion_list = NULL;
    char* output_file = NULL;
    int num_splitters = 0;
    int num_builders = 0;
    int top_k = 0;

    // Parse command-line arguments
    parse_arguments(argc, argv, &input_file, &num_splitters, &num_builders, &top_k, &exclusion_list, &output_file);

    // Create processes
    create_builders(num_builders);
    create_splitters(num_splitters, input_file, exclusion_list);

    // Wait for all child processes to complete
    while (wait(NULL) > 0);

    // Collect and display results
    collect_results(top_k, output_file);

    // Print signal statistics
    printf("Received %d SIGUSR1 signals and %d SIGUSR2 signals.\n", usr1_signals, usr2_signals);

    return 0;
}