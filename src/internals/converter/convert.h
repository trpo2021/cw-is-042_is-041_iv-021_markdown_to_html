#include <internals/parser/ast.h>
#include <internals/parser/collection.h>
#include <internals/strings/strings.h>
#include <internals/taglist/taglist.h>
#include <stdio.h>
#include <string.h>

string convert_node(string head, string content);
string close_tag(string head);
void spec_symblos(string content);
