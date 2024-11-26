#include "splitter.h"

int is_excluded(const char* word, const char* exclusion_list) {
    FILE* excl_file = fopen(exclusion_list, "r");
    if (excl_file == NULL) {
        perror("Failed to open exclusion list");
        return 1;
    }

    char excl_word[256];
    while (fscanf(excl_file, "%255s", excl_word) != EOF) {
        if (strcmp(word, excl_word) == 0) {
            fclose(excl_file);
            return 1;
        }
    }

    fclose(excl_file);
    return 0;
}

// Clean the word by removing non-alphabetic characters
void clean_word(char* word) {
    int i = 0, j = 0;
    while (word[i]) {
        if (isalpha(word[i])) {
            word[j++] = tolower(word[i]);
        }
        i++;
    }
    word[j] = '\0';
}

void process_text_chunk(FILE* file, const char* exclusion_list, int num_builders, int* pipes) {
    char word[256];
    while (fscanf(file, "%255s", word) != EOF) {
        clean_word(word);

        if (strlen(word) == 0 || is_excluded(word, exclusion_list)) {
            continue;
        }

        hash_and_send_words(word, num_builders, pipes);
    }
}

// Function to hash a word and send it to the appropriate builder
void hash_and_send_words(const char* word, int num_builders, int* pipes) {
    unsigned int hash = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        hash = hash * 31 + word[i]; // Simple hash function
    }

    int builder_index = hash % num_builders; // Determine which builder should handle the word
    write(pipes[builder_index * 2 + 1], word, strlen(word) + 1); // Send word to the selected builder
}

// Function to initialize the splitter and process the file
int main(const char* input_file, const char* exclusion_list, int num_builders) {
    FILE* file = fopen(input_file, "r");
    if (file == NULL) {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    // Set up pipes for communication with builders
    int pipes[num_builders * 2]; // Two pipes per builder (one for reading, one for writing)
    for (int i = 0; i < num_builders; i++) {
        if (pipe(&pipes[i * 2]) == -1) {
            perror("Failed to create pipe");
            exit(EXIT_FAILURE);
        }
    }

    // Read the file and process it
    process_text_chunk(file, exclusion_list, num_builders, pipes);

    fclose(file);

    return 0;
}