#define CTEST_MAIN
#include <../src/internals/io/file/reader.h>
#include <../src/internals/io/file/writer.h>
#include <../src/internals/io/std/reader.h>
#include <../src/internals/strings/strings.h>
#include <../src/internals/taglist/taglist.h>
#include <../src/internals/templates/config.h>
#include <ctest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* HELP_CALL =
    "Usage:\n\t./converter -s <input-file-path> -o <output-file-path> (The input and output data are "
    "files)\n\t./converter -o <output-file-path> (The input data is read from the keyboard, the output "
    "data is a file)\n\t./converter (Input data is read from the keyboard, output data is "
    "output to the terminal)\n\t./converter -t <path-to-css> -s <input-file-path> -o <output-file-path> "
    "(If you want to use your own styles)\n";

int main(int argc, const char** argv)
{
    return ctest_main(argc, argv);
}

CTEST(std, help)
{
    ASSERT_STR(HELP_CALL, HELP_CALL);
}