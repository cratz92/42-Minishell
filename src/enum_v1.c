#include "../include/minishell.h"

t_token *ft_evalute_single_token(char **a, int *i)
{
    int     j;
    int     k;
    t_token *tkn;

    j = *i;
    k = 0;
    tkn = malloc(sizeof(t_token));
    tkn->cmd = NULL;
    tkn->args = NULL;
    tkn->args = malloc(sizeof(1000));
    tkn->cmd = a[j];
    if (ft_strlook_char(a[j], '=') && !ft_strexact_abs(a[j - 1], "echo")) //just being carefull, but i think can go away
    {
        tkn->en = 4;
        *i += 1;
        return (tkn);
    }
    else if (a[j][0] == '|')
        tkn->en = 1;
    else if (a[j][0] == '<' || a[j][0] == '>')
        tkn->en = 2;
    else
        tkn->en = 3;
    j++;
    if (ft_strlook(a[j - 1], "<>|") != 1)
        while (a[j] && ft_strlook(a[j], "<>|") != 1)
            tkn->args[k++] = a[j++];
    tkn->args[k] = 0;
    *i = j;
    return (tkn);
}

t_token *ft_evaluate_args_to_token(t_args *a)
{
    t_token *tkn;
    t_token *head;
    t_token *prev;
    int     i;
    t_args  *cpy;

    cpy = a;
    i = 0;
    head = ft_evalute_single_token(a->args, &i);
    prev = NULL;
    tkn = NULL;
    while (a->args[i])
    {
        tkn = ft_evalute_single_token(a->args, &i);
        if (prev)
            prev->next = tkn;
        tkn->prev = prev;
        prev = tkn;
    }
    if (tkn)
    {
        while (tkn->prev != NULL)
            tkn = tkn->prev;
        head->next = tkn;
        tkn->prev = head;
    }
    //free_array(cpy->args); // NOT NEEDED?
    return (head);
}
