#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char **argv) {

    const int buffer_size = 5000;
    char buffer[buffer_size];

    char *fifo_reader = "read_fifo";
    int r_stream = open(fifo_reader, O_RDONLY);

    int b_stream = read(r_stream, buffer, buffer_size);

    close(r_stream);
    remove(r_stream);

    int big = 0;
    int small = 0;
    int answer[2];
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

    char *fifo_fuction = "fifo_a";

    int f_stream = open(fifo_fuction, O_WRONLY);

    write(f_stream, buffer, 2 * sizeof(int));
    close(f_stream);
}