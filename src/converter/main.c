#include <getopt.h>
#include <internals/exceptions/exceptions.h>
#include <internals/io/file/reader.h>
#include <internals/io/file/writer.h>
#include <internals/io/std/reader.h>
#include <internals/memext/memext.h>
#include <internals/templates/config.h>
#include <memory.h>
#include <stdio.h>

static void show_help_msg()
{
    puts("Usage:\n\t./converter -s <input-file-path> -o <output-file-path> (The input and output data are "
         "files)\n\t./converter -o <output-file-path> (The input data is read from the keyboard, the output "
         "data is a file)\n\t./converter (Input data is read from the keyboard, output data is "
         "output to the terminal)\n\t./converter -t <path-to-css> -s <input-file-path> -o <output-file-path> "
         "(If you want to use your own styles)\n");
}

static char* read_content_from_stdin()
{
    puts("Input text via keyboard. For stop - input '-quit' on new line.");
    return read_stdin();
}

static char** parse_commandline_args(int argc, char*** argv)
{
    const char* short_options = "s:o:t:";
    const struct option long_options[] = {{"help", no_argument, NULL, 'h'},
                                          {"source", required_argument, NULL, 's'},
                                          {"output", required_argument, NULL, 'o'},
                                          {"template", required_argument, NULL, 't'},
                                          {NULL, 0, NULL, 0}};
    char** args_options = mem_alloc(255 * sizeof(char*));
    memset(args_options, 0, 255 * sizeof(char*));
    int getopt_result;
    int option_index;
    while ((getopt_result = getopt_long(argc, *argv, short_options, long_options, &option_index)) != -1)
    {
        switch (getopt_result)
        {
        case 'h':
            show_help_msg();
            exit(EXIT_SUCCESS);
        case 'o':
        case 's':
        case 't':
            args_options[getopt_result] = optarg;
            break;
        default:
            throw_exception(ExceptionUnknownArg, "Use --help for more info");
        }
    }
    return args_options;
}

int main(int argc, char** argv)
{
    char** args_options = parse_commandline_args(argc, &argv);
    char* source_content = args_options['s'] ? read_file(args_options['s']) : read_content_from_stdin();
    if (!source_content)
    {
        throw_exception(ExceptionStdinCharacterLimit, "To convert more than 1000 characters, you can use file.\n"
                                                      "Run './converter --help' for more information");
    }
    /* here convert markdown to html */
    /* before it you need to free this */
    free(source_content);
    /* here get template */
    if (args_options['t'])
    {
        /* here replace path to css */
    }
    /* here concat template to converted html */
    if (args_options['o'])
    {
        /* here write html to file */
        free(args_options);
        return EXIT_SUCCESS;
    }
    /* here write html to stdout */
    free(args_options);
    return EXIT_SUCCESS;
}