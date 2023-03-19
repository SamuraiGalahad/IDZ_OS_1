#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv) {

    const int buffer_size = 5000;
    char buffer[buffer_size];

    int b_stream = read(20, buffer, buffer_size);

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

    write(31, buffer, 2 * sizeof(int));
    
}