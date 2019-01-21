#include "sequential.h"

int seq_tests(int progress, char prefix, int file_size, char *file_name) {

    struct timespec t1, t2;
    double dtime, write_speed, read_speed;

    int blockSize = 1024, aux, times, i, counter = 1, iterations = 0, ipercentage = 0;
    char *data = (char*)malloc(blockSize);

    char progress_bar[30] = "[--------------------] ";
    char progress_bar0[] = "[--------------------] ";
    char percentage[5] = "0%";
    char message[] = "Writing file sequentially...";


    FILE *fp;
    
    strcat(progress_bar, percentage);
    
    // Create random block of data.
    for (i = 0; i < blockSize; i++) {
        data[i] = rand() % 256;
    }

    if (prefix == 'M')
        times = 1024;
    else // if equals 'G'
        times = 1024 * 1024;


    fp = fopen(file_name, "wb+");

    if (fp == NULL) {
        printf("Could not open file!\n");
        return EXIT_FAILURE;
    }

    if (progress) 
        printf("%s\t\t%s\r", message, progress_bar);
    else
        printf("\r%s", message);
    
    fflush(stdout);

    clock_gettime(CLOCK_MONOTONIC, &t1);

    aux = times * file_size / 20;

    for (i = 0; i < times * file_size; i ++) {
        
        if (progress) {
            iterations++;
            if (iterations  == aux) {
                iterations = 0;
                    update_bar(&progress_bar[0], &counter, &ipercentage, &percentage[0], &message[0]);
            }
        }

        fwrite(data, sizeof(char), blockSize, fp);
    }

    //system("sync");

    if (progress)
        printf("\r%s\t\t%s\n%s\t\tdone!\n\n", message, message, progress_bar);
    else
        printf("\t\tdone!\n\n");

    reset_bar(&progress_bar[0], &progress_bar0[0], &percentage[0], &counter, &ipercentage);

    clock_gettime(CLOCK_MONOTONIC, &t2);

    dtime = (t2.tv_sec - t1.tv_sec) + (double) (t2.tv_nsec - t1.tv_nsec) * 1e-9;
    write_speed = file_size / dtime;

    if (prefix == 'G')
        write_speed *= 1024;

    printf("%d %cB written in %.4f seconds. Average sequential write speed was %.2f MB/s.\n\n", file_size, prefix, dtime, write_speed); 

    fclose(fp);

    /* Clear cache and redirect output (requires sudo) */
    printf("Clearing cache...\n");
    system("sync ; echo 1 | sudo tee /proc/sys/vm/drop_caches > /dev/null 2>&1");

/* ----- Reading file ----- */

    fp = fopen(file_name, "rb");

    if (fp == NULL) {
        printf("Could not open file!\n");
        return EXIT_FAILURE;
    }

    clock_gettime(CLOCK_MONOTONIC, &t1);

    while(fgetc(fp) != EOF) {}

    clock_gettime(CLOCK_MONOTONIC, &t2);
    
    dtime = (t2.tv_sec - t1.tv_sec) + (double) (t2.tv_nsec - t1.tv_nsec) * 1e-9;

    read_speed = file_size / dtime;
    if (prefix == 'G')
        read_speed *= 1024;

    printf("%.4fs taken to read file. Average sequential read speed was %.2f MB/s\n", dtime, read_speed);


    fclose(fp);

    return EXIT_SUCCESS;
}


void update_bar(char *progress_bar, int *counter, int *ipercentage, char *percentage, char *str) {

        *ipercentage = *ipercentage + 5;
        progress_bar[*counter] = '#';

        (*counter)++;

        sprintf(percentage, "%d", *ipercentage);
        strcat(percentage, "%");

        progress_bar[23] = '\0';
                
        strcat(progress_bar, percentage);

        printf("\r%s\t\t%s", str, progress_bar);
    
        fflush(stdout);
}

void reset_bar(char *pbar, char *pbar0, char *percentage, int *counter, int *ipercentage) {
    *counter = 1;
    *ipercentage = 0;
    strcpy(percentage, "0%");
    strcpy(pbar, pbar0);
}

