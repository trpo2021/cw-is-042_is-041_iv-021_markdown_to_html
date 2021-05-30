#pragma once

#include <internals/strings/strings.h>
#include <stdbool.h>

bool validate_url(String* content);
bool validate_email(String* content);