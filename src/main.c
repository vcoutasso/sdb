#include "sequential.h"

int is_digit(char ch);


int main(int argc, char **argv) {

    srand(time(NULL));

    int progress = 0;

    char file_name[20] = "file_sdb", prefix = 'M';
    int i, file_size = 1024;
    int clear_cache = 0;


    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-of") == 0 || strcmp(argv[i], "--ouput-file") == 0 ) {
            strcpy(file_name, argv[i + 1]);
            i += 1;
        }
        else if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--size") == 0) {

            if ((argv[i+1][strlen(argv[i+1]) - 2] == 'M') && (argv[i+1][strlen(argv[i+1]) - 1] == 'B')) {
                file_size = atoi(argv[i+1]);
                prefix = 'M';
            }
            else if ((argv[i + 1][strlen(argv[i + 1]) - 2] == 'G') && (argv[i+1][strlen(argv[i+1]) -1] == 'B' )){
                file_size = atoi(argv[i+1]);
                prefix = 'G';
            }
            else {
                printf("Invalid parameter\n");
                return EXIT_FAILURE;
            }
            i += 1;
        }
        else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--clear-cache") == 0) {
                clear_cache = 1;
        }
        else if (strcmp(argv[i], "-p") == 0) {
            progress = 1;
        }
        else {
            printf("Unrecognized argument %s. Exiting script\n", argv[i]);
            return EXIT_FAILURE;
        }
    
    }


    if (seq_tests(progress, prefix, file_size, &file_name[0], clear_cache) == EXIT_FAILURE)
        return EXIT_FAILURE;


    return EXIT_SUCCESS;
}

int is_digit(char ch) {
    if (ch >= '0' && ch <= '9')
        return 1;

    return 0;
}
