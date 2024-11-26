#include "builder.h"

void init_builder(int builder_id, int read_fd, int write_fd) {
    // Initialize the data structure for word counting
    void* word_count_map = init_data_structure();

    char word[256];  // Buffer to read incoming words

    // Read words sent from splitters
    while (read(read_fd, word, sizeof(word)) > 0) {
        count_word(word_count_map, word);
    }

    // Send results back to the root
    send_results_to_root(word_count_map, write_fd);

    // Free memory
    free_data_structure(word_count_map);
}

// Send word frequency results to the root process
void send_results_to_root(void* word_count_map, int write_fd) {
    char result_line[512];

    // Iterate through the data structure and send word counts
    while (get_next_word_count(word_count_map, result_line, sizeof(result_line))) {
        write(write_fd, result_line, strlen(result_line) + 1);
    }

    // Send an end marker
    const char* end_marker = "END\n";
    write(write_fd, end_marker, strlen(end_marker) + 1);
}