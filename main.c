#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char **argv) {

    srand(time(NULL));

    int blockSize = 1024;
    char *str = (char*)malloc(blockSize);

    struct timespec t2, t3;
    double dt1, write_speed, read_speed;

    int i;

    FILE *ptr;

    // Create random block of data.
    for (i = 0; i < blockSize; i++) {
        str[i] = rand() % 256;
    }

    ptr = fopen(argv[1], "wb+");

    clock_gettime(CLOCK_MONOTONIC, &t2);

    for (i = 0; i < 1024 * atoi(argv[2]); i ++) {
        fwrite(str, sizeof(char), 1024, ptr);
    }

    clock_gettime(CLOCK_MONOTONIC, &t3);

    dt1 = (t3.tv_sec - t2.tv_sec) + (double) (t3.tv_nsec - t2.tv_nsec) * 1e-9;
    write_speed = atoi(argv[2]) / dt1;

    printf("%d MB written in %.4f seconds. Sequential write speed was %.2f MB/s\n\n", atoi(argv[2]), dt1, write_speed); 

    fclose(ptr);


    ptr = fopen(argv[1], "rb");

    clock_gettime(CLOCK_MONOTONIC, &t2);

        while(fgetc(ptr) != EOF) {}

    clock_gettime(CLOCK_MONOTONIC, &t3);
    
    dt1 = (t3.tv_sec - t2.tv_sec) + (double) (t3.tv_nsec - t2.tv_nsec) * 1e-9;

    read_speed = atoi(argv[2]) / dt1;

    printf("%.4fs taken to read file. Sequential read speed was %.2f MB/s\n", dt1, read_speed);


    fclose(ptr);


    return 0;
}
