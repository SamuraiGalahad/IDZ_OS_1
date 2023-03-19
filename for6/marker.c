#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

const int buffer_size = 5000;
char buffer[buffer_size];

int main(int argc, char **argv) {
    int filed;
    ssize_t written_bytes;
    filed = open(argv[1], O_RDONLY);

    // Чтение
    if (filed < 0)
    {
        fprintf(stderr, "Error!");
        exit(1);
    }

    ssize_t b_stream = read(filed, buffer, buffer_size);

    if (b_stream < 0)
    {
        fprintf(stderr, "Error!");
        exit(1);
    }
    close(filed);
    write(21, buffer, b_stream);

    // Запись
    int res[2];
    b_stream = read(30, buffer, buffer_size);
    if (b_stream < 0)
    {
        fprintf(stderr, "Error!");
        exit(1);
    }
    filed = open(argv[2], O_WRONLY);

    memcpy(res, buffer, b_stream);
    sprintf(buffer, "%d", res[0]);
    sprintf(&buffer[sizeof(int)], "%d", res[1]);

    written_bytes = write(filed, buffer, b_stream);

    if (written_bytes != b_stream)
    {
        fprintf(stderr, "Error!");
        exit(1);
    }

    close(filed);
    exit(0);

    return 0;
}