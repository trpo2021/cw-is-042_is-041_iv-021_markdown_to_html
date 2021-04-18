#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct
{
    char *key;
    char *value;
} Tag;

typedef struct
{
    Tag tags[100];
} TagList;

TagList list = {
    .tags[0] = {"# ", "<h1>"},
    .tags[1] = {"=", "<h1>"},
    .tags[2] = {"-", "<h2>"},
    .tags[3] = {"## ", "<h2>"},
    .tags[4] = {"### ", "<h3>"},
    .tags[5] = {"#### ", "<h4>"},
    .tags[6] = {"##### ", "<h5>"},
    .tags[7] = {"######", "<h6>"},
    .tags[8] = {"**", "<strong>"},
    .tags[9] = {"__", "<strong>"},
    .tags[10] = {"*", "<em>"},
    .tags[11] = {"_", "<em>"},
    .tags[12] = {"***", "<strong><em>"},
    .tags[13] = {"___", "<strong><em>"},
    .tags[14] = {"  \n\n", "<br>"},
    .tags[15] = {">", "<blockquote>\n<p>"},
    .tags[16] = {">>", "<blockquote>\n<p>"},
    .tags[17] = {">>>", "<blockquote>\n<p>"},
    .tags[18] = {"1.", "<ol>\n<li>"},
    .tags[19] = {"1)", "<ol>\n<li>"},
    .tags[20] = {"- ", "<ul>\n<li>"},
    .tags[21] = {"* ", "<ul>\n<li>"},
    .tags[22] = {"+ ", "<ul>\n<li>"},
    .tags[23] = {"        ", "<pre><code>"},
    .tags[24] = {"***", "<hr>"},
    .tags[25] = {"---", "<hr>"},
    .tags[26] = {"___", "<hr>"},
    .tags[27] = {"`", "<code>"},
    .tags[28] = {"    ", "<pre><code>"}};

