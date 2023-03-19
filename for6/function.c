#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

const int buffer_size = 5000;
char buffer[buffer_size];

void verifyDocs(char **argv) {
    if (access(argv[1], F_OK) != 0) {
        fprintf(stderr, "Wrong file name!");
        exit(1);
    }
    
    if (access(argv[2], F_OK) != 0) {
        fprintf(stderr, "Wrong file name!");
        exit(1);
    }
}


int main(int argc, char **argv) {

    if (argc < 3) {
        fprintf(stderr, "No file arguments!");
        exit(1);
    }

    verifyDocs(argv);

    int fd[2];
    int fd_2[2];

    pipe(fd);
    pipe(fd_2);

    int i;

    for (int i = 0; i < 2; ++i) {
        dup2(fd[i], i + 20);
        dup2(fd_2[i], i + 30);
    }

    if (fork()) {
        execv("./marker.o", argv);
    }

    int big = 0;
    int small = 0;
    int answer[2];
    ssize_t b_stream = read(fd[0], buffer, buffer_size);

    for (int i = 0; i < b_stream; i++)
    {
        if ('A' <= buffer[i] && 'Z' >= buffer[i])
        {
            big++;
        }
        if ('a' <= buffer[i] && 'z' >= buffer[i])
        {
            small++;
        }
    }

    answer[0] = big;
    answer[1] = small;

    memcpy(buffer, answer, 2 * sizeof(int));

    write(fd_2[1], buffer, 2 * sizeof(int));

    close(fd[0]);
    close(fd[1]);
    close(20);
    close(21);
    close(fd_2[0]);
    close(fd_2[1]);
    close(30);
    close(31);
}