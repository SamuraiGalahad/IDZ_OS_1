#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
        execv("./reader.o", argv);
    }
    if (fork()) {
        execv("./function.o", argv);
    }
    if (fork()) {
        execv("./writer.o", argv);
    }

    close(fd[0]);
    close(fd[1]);
    close(20);
    close(21);
    close(fd_2[0]);
    close(fd_2[1]);
    close(30);
    close(31);
}