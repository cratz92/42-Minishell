#include "../include/minishell.h"

t_token *init_tkn(char *str)
{
    t_token *tkn;

    tkn = malloc(sizeof(t_token));
    tkn->cmd = NULL;
    tkn->args = NULL;
    tkn->next = NULL;
    tkn->args = malloc(sizeof(1000));
    tkn->cmd = str;
    return (tkn);
}

t_token *ft_evalute_single_token(char **a, int *i)
{
    int     k;
    t_token *tkn;

    tkn = init_tkn(a[*i]);
    if (ft_strlook_char(tkn->cmd, '=')) //&& !ft_strexact_abs(a[*i - 1], "echo") -just being carefull, but i think can go away
        tkn->en = 4;
    else if (tkn->cmd[0] == ';')
        tkn->en = 5;
    else if (tkn->cmd[0] == '|')
         tkn->en = 1;
    else if (tkn->cmd[0] == '<' || tkn->cmd[0] == '>')
        tkn->en = 2; //<< >> can be added if needed
    else
        tkn->en = 3;
    *i += 1;
    if (ft_strlook(tkn->cmd, "<>|;"))
        return (tkn);
    k = 0;
    while (a[*i] && !ft_strlook(a[*i], "<>|;"))
    {
        tkn->args[k] = malloc(sizeof(char) * ft_strlen(a[*i]));
        tkn->args[k++] = a[*i];
        *i += 1;
    }
    tkn->args[k] = 0;
    return (tkn);
}

t_token *ft_evaluate_args_to_token(t_args *a)
{
    t_token *tkn;
    t_token *head;
    t_token *prev;
    int     i;
    // t_args  *cpy;

    // cpy = a;
    i = 0;
    head = ft_evalute_single_token(a->args, &i);
    prev = NULL;
    tkn = NULL;
    while (a->args[i])
    {
        // printf("eval:%s\n", a->args[i]);
        tkn = ft_evalute_single_token(a->args, &i);
        // printf("eval:%s\n", tkn->cmd);
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
