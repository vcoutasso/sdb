#ifndef _sequential_h
#define _sequential_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

int seq_tests(int verbose, char prefix, int file_size, char *file_name);

void update_bar(char *progress_bar, int *counter, int *ipercentage, char *percentage, char *str);

void reset_bar(char *pbar, char *pbar0, char *percentage, int *counter, int *ipercentage);

#endif
