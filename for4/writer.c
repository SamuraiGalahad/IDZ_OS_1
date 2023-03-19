#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

void sys_err(char *msg)
{
    puts(msg);
    exit(1);
}

int main(int argc, char **argv) {
    const ssize_t buffer_size = 5000;
    char buffer[buffer_size];
    int answer[2];
    ssize_t b_stream = read(30, buffer, buffer_size);

    int stream = open(argv[2], O_WRONLY);

    memcpy(answer, buffer, b_stream);
    sprintf(buffer, "%d", answer[0]);
    sprintf(&buffer[sizeof(int)], "%d", answer[1]);

    int w_stream = write(stream, buffer, b_stream);

    if (b_stream != w_stream) {
        fprintf(stderr, "Problem with write in file!\n");
        exit(1);
    }

    close(stream);
    exit(0);
}