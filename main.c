#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

int is_digit(char ch) {
    if (ch >= '0' && ch <= '9')
        return 1;

    return 0;
}

int main(int argc, char **argv) {

    srand(time(NULL));

    int blockSize = 1024, times;
    char *str = (char*)malloc(blockSize), file_name[20], prefix;

    struct timespec t1, t2;
    double dtime, write_speed, read_speed;

    int i, file_size;

    FILE *ptr;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-of") == 0) {
            strcpy(file_name, argv[i + 1]);
            i += 1;
        }
        else if (strcmp(argv[i], "-s") == 0) {

            if(argv[i + 1][strlen(argv[i + 1]) - 1] == 'M' ||  is_digit(argv[i + 1][strlen(argv[i + 1]) - 1])) {
                file_size = atoi(argv[i+1]);
                prefix = 'M';
            }
            else if (argv[i + 1][strlen(argv[i + 1]) - 1] == 'G') {
                file_size = atoi(argv[i+1]);
                prefix = 'G';
            }
            else {
                printf("Invalid parameter\n");
                return EXIT_FAILURE;
            }
            i += 1;
        }
        else {
            printf("Unrecognized argument %s. Exiting script\n", argv[i]);
            return EXIT_FAILURE;
        }
    
    }

    // Create random block of data.
    for (i = 0; i < blockSize; i++) {
        str[i] = rand() % 256;
    }

    if (prefix == 'M')
        times = 1024;
    else // if equals 'G'
        times = 1024 * 1024;

    ptr = fopen(file_name, "wb+");

    clock_gettime(CLOCK_MONOTONIC, &t1);

    for (i = 0; i < times * file_size; i ++) {
        fwrite(str, sizeof(char), blockSize, ptr);
    }

    clock_gettime(CLOCK_MONOTONIC, &t2);

    dtime = (t2.tv_sec - t1.tv_sec) + (double) (t2.tv_nsec - t1.tv_nsec) * 1e-9;
    write_speed = file_size / dtime;

    if (prefix == 'G')
        write_speed *= 1024;

    printf("%d %cB written in %.4f seconds. Sequential write speed was %.2f MB/s\n\n", file_size, prefix, dtime, write_speed); 

    fclose(ptr);


    ptr = fopen(file_name, "rb");

    clock_gettime(CLOCK_MONOTONIC, &t1);

    while(fgetc(ptr) != EOF) {}

    clock_gettime(CLOCK_MONOTONIC, &t2);
    
    dtime = (t2.tv_sec - t1.tv_sec) + (double) (t2.tv_nsec - t1.tv_nsec) * 1e-9;

    read_speed = file_size / dtime;
    if (prefix == 'G')
        read_speed *= 1024;

    printf("%.4fs taken to read file. Average sequential read speed was %.2f MB/s\n", dtime, read_speed);


    fclose(ptr);


    return EXIT_SUCCESS;
}
