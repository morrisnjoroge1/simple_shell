#include "shell.h"
void line_handler(char **line, ssize_t read);
void ops_logic(char *line, ssize_t *new_len);
ssize_t new_length(char *line);

/**
* line_handler - divides a line read from standard input as needed.
* @line:  pointer  from standard input.
* @read: line read from standard input pointer.
*
* Description: Spaces are inserted to separate ";", "||", and "&&".
*              Replaces "#" with '\0'.
*/
void line_handler(char **line, ssize_t read)
{
char *old_line, *new_line;
char previous, current, next;
size_t i, k;
ssize_t new_len;

new_len = new_length(*line);
if (new_len == read - 1)
return;
new_line = malloc(new_len + 1);
if (!new_line)
return;
k = 0;
old_line = *line;
for (i = 0; old_line[i]; i++)
{
current = old_line[i];
next = old_line[i + 1];
if (i != 0)
{
previous = old_line[i - 1];
if (current == ';')
{
if (next == ';' && previous != ' ' && previous != ';')
{
new_line[k++] = ' ';
new_line[k++] = ';';
continue;
}
else if (previous == ';' && next != ' ')
{
new_line[k++] = ';';
new_line[k++] = ' ';
continue;
}
if (previous != ' ')
new_line[k++] = ' ';
new_line[k++] = ';';
if (next != ' ')
new_line[k++] = ' ';
continue;
}
else if (current == '&')
{
if (next == '&' && previous != ' ')
new_line[k++] = ' ';
else if (previous == '&' && next != ' ')
{
new_line[k++] = '&';
new_line[k++] = ' ';
continue;
}
}
else if (current == '|')
{
if (next == '|' && previous != ' ')
new_line[k++]  = ' ';
else if (previous == '|' && next != ' ')
{
new_line[k++] = '|';
new_line[k++] = ' ';
continue;
}
}
}
else if (current == ';')
{
if (i != 0 && old_line[i - 1] != ' ')
new_line[k++] = ' ';
new_line[k++] = ';';
if (next != ' ' && next != ';')
new_line[k++] = ' ';
continue;
}
new_line[k++] = old_line[i];
}
new_line[k] = '\0';

free(*line);
*line = new_line;
}


/**
* new_length - new length of a line divided
*               by ";", "||", "&", or "#".
* @line: pointer line to check.
*
* Return: length of the line.
*
* Description: Cuts short lines containing '#' comments with '\0'.
*/

ssize_t new_length(char *line)
{
size_t i;
ssize_t new_len = 0;
char current, next;

for (i = 0; line[i]; i++)
{
current = line[i];
next = line[i + 1];
if (current == '#')
{
if (i == 0 || line[i - 1] == ' ')
{
line[i] = '\0';
break;
}
}
else if (i != 0)
{
if (current == ';')
{
if (next == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
{
new_len += 2;
continue;
}
else if (line[i - 1] == ';' && next != ' ')
{
new_len += 2;
continue;
}
if (line[i - 1] != ' ')
new_len++;
if (next != ' ')
new_len++;
}
else
ops_logic(&line[i], &new_len);
}
else if (current == ';')
{
if (i != 0 && line[i - 1] != ' ')
new_len++;
if (next != ' ' && next != ';')
new_len++;
}
new_len++;
}
return (new_len);
}


/**
* ops_logic - Checks a line for logical operators "||" or "&&".
* @line: pointer character to check in the line.
* @new_len: Pointer to new_len in new_lenght function.
*/

void ops_logic(char *line, ssize_t *new_len)
{
char prev, curr, next;

prev = *(line - 1);
curr = *line;
next = *(line + 1);

if (curr == '&')
{
if (next == '&' && prev != ' ')
(*new_len)++;
else if (prev == '&' && next != ' ')
(*new_len)++;
}
else if (curr == '|')
{
if (next == '|' && prev != ' ')
(*new_len)++;
else if (prev == '|' && next != ' ')
(*new_len)++;
}
}
