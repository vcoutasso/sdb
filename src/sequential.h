#ifndef _sequential_h
#define _sequential_h

#define _GNU_SOURCE
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_BOLD          "\x1b[1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int seq_tests(int verbose, char prefix, int file_size, char *file_name, int clear_cache);

void update_bar(char *progress_bar, int *counter, int *ipercentage, char *percentage, char *str);

void reset_bar(char *pbar, char *pbar0, char *percentage, int *counter, int *ipercentage);

#endif
