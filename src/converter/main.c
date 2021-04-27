#include <internals/io/file/reader.h>
#include <internals/io/file/writer.h>
#include <internals/io/std/reader.h>
#include <internals/strings/strings.h>
#include <internals/taglist/taglist.h>
#include <internals/templates/config.h>
#include <stdio.h>

const char* HELP_CALL =
    "Usage:\n\t./converter -s <input-file-path> -o <output-file-path> (The input and output data are "
    "files)\n\t./converter -o <output-file-path> (The input data is read from the keyboard, the output "
    "data is a file)\n\t./converter (Input data is read from the keyboard, output data is "
    "output to the terminal)\n\t./converter -t <path-to-css> -s <input-file-path> -o <output-file-path> "
    "(If you want to use your own styles)\n";

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        printf("%s\n", HELP_CALL);
        printf("Use \"-quit\" to exit input field\n");
        char* buf = calloc(STDIN_LIMIT, 1);
        int check_flag = stdin_read(buf);
        if (check_flag == 1)
        {
            print_error_stdin_read(STDIN_LIMIT_RECHEAD_CODE);
            return -1;
        }

        printf("\nYour HTML code:\n");
        printf("%s", buf);
        free(buf);
        return 0;
    }

    if (strcmp(argv[1], "-t") == 0 && fopen(argv[2], "r") == NULL)
    {
        printf("File \"%s\" not found\nDefault styles \"style.css\" created", argv[2]);
        create_css();
    }
    else
    {
        create_css();
    }
    // Input data is read from the keyboard, output data is output to the terminal

    if (strcmp(argv[1], "--help") == 0)
    {
        printf("%s", HELP_CALL);
        return 0;
    }
    // If you want to use your own styles
    else if (strcmp(argv[1], "-t") == 0 && fopen(argv[2], "r") != NULL)
    {
        if (strcmp(argv[3], "-s") == 0 && strcmp(argv[5], "-o") == 0)
        {
            if (fopen(argv[4], "r") == NULL)
            {
                printf("\nFile \"%s\" not found\n\n", argv[4]);
                printf("%s", HELP_CALL);
                return -1;
            }
            if (fopen(argv[6], "r") == NULL)
            {
                printf("\nFile \"%s\" not found\n\n", argv[6]);
                printf("%s", HELP_CALL);
                return -1;
            }
            else
            {
                read_file(argv[4]);
                write_file(argv[6], "test");
            }
        }
        return 0;
    }
    // The input and output data are files
    else if (strcmp(argv[1], "-s") == 0 && strcmp(argv[3], "-o") == 0)
    {
        if (fopen(argv[2], "r") == NULL)
        {
            printf("\nFile \"%s\" not found\n\n", argv[2]);
            printf("%s", HELP_CALL);
            return -1;
        }
        if (fopen(argv[4], "r") == NULL)
        {
            printf("\nFile \"%s\" not found\n\n", argv[4]);
            printf("%s", HELP_CALL);
            return -1;
        }
        else
        {
            read_file(argv[2]);
            write_file(argv[4], "test");
        }
        return 0;
    }
    // The input data is read from the keyboard, the output data is a file
    else if (strcmp(argv[1], "-o") == 0)
    {
        printf("Use \"-quit\" to exit input field\n");
        char* buf = calloc(STDIN_LIMIT, 1);
        int check_flag = stdin_read(buf);
        if (check_flag == 1)
        {
            print_error_stdin_read(STDIN_LIMIT_RECHEAD_CODE);
            return -1;
        }

        write_file(argv[2], buf);
        free(buf);
        return 0;
    }
    else
    {
        printf("\n---------------\n");
        printf("Incorrect input\n");
        printf("---------------\n");
        printf("%s\n", HELP_CALL);
        remove("style.css");
    }
}