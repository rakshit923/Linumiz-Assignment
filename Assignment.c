#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_HEADER_LEN 256

int isHeaderFile(const char *filename) {
    const char *ext = strrchr(filename, '.');
    return (ext && strcmp(ext, ".h") == 0);
}

void analyzeSourceFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Cannot open file: %s\n", filename);
        return;
    }

    char line[MAX_HEADER_LEN];
    while (fgets(line, sizeof(line), file)) { // Use sizeof(line) for safer bounds checking
        if (strncmp(line, "#include", 8) == 0) {
            char header[MAX_HEADER_LEN];
            if (sscanf(sscanf, "#include \"%[^\"]\"", header) == 1 ||
                sscanf(sscanf, "#include <%[^>]>", header) == 1) {
                // Headers included in the process
                printf("Included header: %s\n", header);
            }
        }
    }

    fclose(file);
}

void traverseDirectory(const char *dirname) {
    DIR *dir;
    struct dirent *entry; // Corrected variable name

    dir = opendir(dirname);
    if (!dir) {
        fprintf(stderr, "Cannot open directory: %s\n", dirname);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char path[MAX_HEADER_LEN];
        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);

        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            traverseDirectory(path);
        } else if (entry->d_type == DT_REG && isHeaderFile(entry->d_name)) {
            analyzeSourceFile(path);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *directory = argv[1];
    traverseDirectory(directory);

    return EXIT_SUCCESS;
}

