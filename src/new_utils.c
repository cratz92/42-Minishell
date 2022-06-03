#include "../include/minishell.h"

char  *ft_strldup(char *str, int l)
{
  char  *dest;
  int   i;

  dest = malloc(sizeof(char) * l + 1);
  if (dest == NULL)
    return (0);
  i = 0;
  while (i < l)
  {
    dest[i] = str[i];
    i++;
  }
  dest[i] = '\0';
  // free(str); Should I?? probably not
  return (dest);
}

char  *ft_strfdup(char **str, int f)
{
  char  *out;
  char  *str2;
  int   i;

  str2 = *str;
  i = 0;
  while(**str != f)
  {
    if (**str == 0)
      break;
    (*str)++;
    i++;
  }
  out = ft_strldup(str2, i);
  return (out);
}

int ft_strlook(char *str)
{
  while (*str)
  {
    if (*str == '>' || *str == '>' || *str == '|') // ... >> <<
      return (1);
    str++;
  }
  return (0);
}

//printing utils for debugging
void  print_targs(t_args *a)
{
  int i;

  i = 0;
  // printf("nbr_pipes=%d nbr_endline=%d\n", a->nbr_pipes, a->nbr_endline);
  printf("----*\n");
  while(a->args[i])
  {
    printf("%s\n", a->args[i++]);
  }
  printf("----*\n");
}

void  print_tkn(t_token *t)
{
  int i;

  i = 0;
  printf("----*\n");
  printf("CMD:%s|%d\n----\n", t->cmd, t->en);
  while(t->args[i])
  {
    printf("%s\n", t->args[i++]);
  }
  printf("----*\n");
  if (t->next)
  {
    printf("NEXT*\n");
    print_tkn(t->next);
  }
}

