#include "files.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);

    if (argc < 3) {
        fprintf(stderr, "Usage: %s tokenize <filename>\n", argv[0]);
        return 1;
    }

    const char *command = argv[1];
    if (strcmp(command, "tokenize") == 0) {
        char *file_contents = readFile(argv[2]);
        if (file_contents == NULL) {
            return 1;
        }

        // tokenizing...

        free(file_contents);
    } else {
        fprintf(stderr, "Unknown command: %s\n", command);
        return 1;
    }
    return 0;
}
