#include "../include/minishell.h"



void ft_evaluate_args(t_args **arg)
{
    t_args    *a;

    a = *arg;
    print_targs(a);
}

/*
if a[0]
--- ls|grep e
ls|grep (... waiting for input)


*/