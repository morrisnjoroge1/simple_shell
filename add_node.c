#include "shell.h"

alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

/**
* add_alias_end - function that Adds a node .
* @head: pointer to the head .
* @name: name of the new alias.
* @value: value of the new alias .
*
* Return: error  - NULL.
*         Otherwise - a pointer to the new node.
*/
alias_t *add_alias_end(alias_t **head, char *name, char *value)
{
alias_t *new_node = malloc(sizeof(alias_t));
alias_t *l;

if (!new_node)
return (NULL);

new_node->next = NULL;
new_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
if (!new_node->name)
{
free(new_node);
return (NULL);
}
new_node->value = value;
_strcpy(new_node->name, name);

if (*head)
{
l = *head;
while (l->next != NULL)
l = l->next;
l->next = new_node;
}
else
*head = new_node;

return (new_node);
}

/**
* add_node_end - function that Adds a node .
* @head: pointer to the head .
* @dir: directory path .
*
* Return: error- NULL.
*         Otherwise - a pointer to the new node.
*/
list_t *add_node_end(list_t **head, char *dir)
{
list_t *new_node = malloc(sizeof(list_t));
list_t *last;

if (!new_node)
return (NULL);

new_node->dir = dir;
new_node->next = NULL;

if (*head)
{
last = *head;
while (last->next != NULL)
last = last->next;
last->next = new_node;
}
else
*head = new_node;

return (new_node);
}

/**
* free_alias_list - function that frees alias.
* @head: head of the alias_t list.
*/
void free_alias_list(alias_t *head)
{
alias_t *next;

while (head)
{
next = head->next;
free(head->name);
free(head->value);
free(head);
head = next;
}
}

/**
* free_list - function thta frees a list_t linked list.
* @head: head of the list_t.
*/
void free_list(list_t *head)
{
list_t *next;

while (head)
{
next = head->next;
free(head->dir);
free(head);
head = next;
}
}


