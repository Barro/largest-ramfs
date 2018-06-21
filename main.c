#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "largest-tmpfs.h"

#ifndef LARGEST_TMPFS_VERSION
#define LARGEST_TMPFS_VERSION devbuild
#endif /* LARGEST_TMPFS_VERSION */

#define STR_MACRO_VALUE(value) STR_MACRO_VALUE_(value)
#define STR_MACRO_VALUE_(value) #value

static void print_usage(const char* program_name, FILE* out)
{
    fprintf(out, "USAGE: %s [OPTION]\n", program_name);
    fputs("\n", out);
    fputs("OPTIONS:\n", out);
    fputs("  -h, --help  Show this help and exit\n", out);
    fputs("  --version   Show version information\n", out);
    fputs("\n", out);
    fputs(
"Prints the path to a memory based file system with the most free space when\n"
"no arguments are given. Does not print anything and returns with non-zero\n"
"value if there is no such file system available.\n", out);
}

int main(int argc, char* argv[])
{
    if (argc > 1) {
        if (strcmp(argv[1], "--version") == 0) {
            puts("largest-tmpfs " STR_MACRO_VALUE(LARGEST_TMPFS_VERSION));
            return EXIT_SUCCESS;
        } else if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            print_usage(argv[0], stdout);
            return EXIT_SUCCESS;
        } else {
            fprintf(stderr, "Unknown argument: %s\n", argv[1]);
            print_usage(argv[0], stderr);
            return EXIT_FAILURE;
        }
    }
    const char* tmpfs_path = largest_tmpfs_get(1024 * 1024);
    if (tmpfs_path == NULL) {
        return EXIT_FAILURE;
    }
    puts(tmpfs_path);
    return EXIT_SUCCESS;
}
