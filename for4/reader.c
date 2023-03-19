#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

const int buffer_size = 5000;
char buffer[buffer_size];

int main(int argc, char **argv) {

    int stream = open(argv[1], O_RDONLY);

    if (stream < 0) {
        fprintf(stderr, "Problem with input file descriptor!");
    }
    
    ssize_t b_stream = read(stream, buffer, buffer_size);

    if (b_stream < 0) {
        fprintf(stderr, "Problem with reading file!");
        exit(1);
    }
    close(stream);
    write(21, buffer, b_stream);
    return 0;
}