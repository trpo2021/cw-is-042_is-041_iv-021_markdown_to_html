#include <stdio.h>

int main(int argc, char** argv)
{
    if (fopen("template_top.html", "r") == NULL || fopen("template_bottom.html", "r") == NULL ||
        fopen("template.css", "r") == NULL)
    {
        create_template();
    }

    if (strcmp("-f", argv[1]) == 0 && strcmp("-f", argv[3]) == 0)
    {
        func_1(read_file(argv[2]), create_out_file(argv[4]));
    }
    else if (strcmp("-d", argv[1]) == 0 && strcmp("-f", argv[3] == 0))
    {
        func_2(read_line(), create_out_file(argv[4]));
    }
    else if (strcmp("-d", argv[1]) == 0 && strcmp("-d", argv[3]) == 0)
    {
        func_3(read_line(), stdout);
    }
    else if (strcmp("-help", argv[1]) == 0)
    {
        printf("Usage:\n\tconverter -f <in-file-name> -f <out-file-name> (The input and output data are "
               "files)\n\tconverter -d stdin -f <out-file-name> (The input data is read from the keyboard, the output "
               "data is a file)\n\tconverter -d stdin -d stdout (Input data is read from the keyboard, output data is "
               "output to the terminal)\n\tconverter -help (Call help)");
    }
    else
        printf("Usage:\n\tconverter -f <in-file-name> -f <out-file-name> (The input and output data are "
               "files)\n\tconverter -d stdin -f <out-file-name> (The input data is read from the keyboard, the output "
               "data is a file)\n\tconverter -d stdin -d stdout (Input data is read from the keyboard, output data is "
               "output to the terminal)\n\tconverter -help (Call help)");
}