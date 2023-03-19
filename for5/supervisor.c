#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

void verifyDocs(char **argv) {
    if (access(argv[1], F_OK) != 0) {
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

    char *fifo_reader = "read_fifo_3";
    char *fifo_fuction = "fifo_a_3";

    if (mkfifo(fifo_reader, 0777))
    {
        perror("mkfifo");
        return 1;
    }
    if (mkfifo(fifo_fuction, 0777))
    {
        perror("mkfifo");
        return 1;
    }

    if (fork())
    {
        execv("./reader.o", argv);
    }
    if (fork())
    {
        execv("./function.o", argv);
    }
    if (fork())
    {
        execv("./writer.o", argv);
    }
    return 0;
}