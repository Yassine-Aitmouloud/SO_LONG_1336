# include "so_long.h"
void add_to_garbage(t_garbage **garbage, void *ptr)
{
    t_garbage *new;

    new = malloc(sizeof(t_garbage));
    if (!new)
    {
        write(2, "Error\nmalloc\n", 13);
        exit(0);
    }
    new->ptr = ptr;
    new->next = *garbage;
    *garbage = new;
}
void clean_garbage(t_garbage **garbage)
{
    t_garbage *tmp;

    while (*garbage)
    {
        tmp = *garbage;
        *garbage = (*garbage)->next;
        free(tmp->ptr);
        free(tmp);
    }
}
