#pragma once

#define STDIN_EXIT_CODE 0
#define STDIN_LIMIT_RECHEAD_CODE 1

// max count of chars read from stdin
static const int STDIN_LIMIT = 1000;

int stdin_read(char* buf);
void print_error_stdin_read(int code);