#include "../include/minishell.h"

// void    ft_evalute_single_token(t_args *arg, t_token *tkn)
// {

// }

        // tkn = malloc(sizeof(t_token));
        // tkn->cmd = a->args[i++];
        // tkn->args = NULL;
        // if (a->args[i] && ft_strlook(tkn->cmd) != 1)
        // {

        // }
        // else if ()


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
    if (ft_strlook(a[j], "="))
    {
        tkn->en = 4;
        *i += 1;
        return (tkn);
    }
     if (a[j][0] == '|')
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

    i = 0;
    head = ft_evalute_single_token(a->args, &i);
        // print_tkn(head);
        // printf("i is %d\n", i);
    prev = NULL;
    tkn = NULL;
    while (a->args[i])
    {
        tkn = ft_evalute_single_token(a->args, &i);
            // print_tkn(tkn);
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
    return (head);
}


/*
if a[0]
--- ls|grep e
token1->cmd = ls
token2->cmd = |
token3->cmd = grep /->args[1] = e

*/