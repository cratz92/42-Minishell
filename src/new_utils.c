#include "../include/minishell.h"

char	*ft_strldupimp(char *str, int i, int j)
{
	char	*dest;
	int		k;
	
	if (i == j)
		return (0);
	dest = malloc(sizeof(char) * (j - i) + 1);
	if (dest == NULL)
		return (0);
	k = 0;
	while(i <= j)
	{
		dest[k++] = str[i++];
	}
	dest[k] = 0;
	return (dest);
}

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

bool  ft_strlook_char(char *str, char l)
{
  int i;

  if (!str || !l)
    return (false);
  while (*str)
  {
      if (*str == l)
        return (true);
    str++;
  }
  return (false);
}

bool  ft_strlook(char *str, char *look)
{
  int i;

  if (!str || !look)
    return (false);
  while (*str)
  {
    i = 0;
    while (look[i])
    {
      if (*str == look[i])
        return (true);
      i++;
    }
    str++;
  }
  return (false);
}

bool	ft_strexact(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (false);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (false);
	while (*s1)
	{
		if (*s1 != *s2)
			return (false);
		s1++;
		s2++;
	}
	return (true);
}

bool	ft_strexact_abs(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (false);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (false);
	while (*s1)
	{
    *s1 = ft_tolower(*s1);
    *s2 = ft_tolower(*s2);
		if (*s1 != *s2)
			return (false);
		s1++;
		s2++;
	}
	return (true);
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

  if (!t)
    return ;
  printf("-----*\n");
  printf("CMD:%s|%d(enum)\n", t->cmd, t->en);
  i = 0;
  while(t->args[i])
  {
    if (t->args[i])
      printf("%s\n", t->args[i++]); //there is a problem here when we have more than 3....
  }
  if (t->next != NULL)
  {
    printf("NEXT-*\n");
    print_tkn(t->next);
  }
}

void  print_var(t_var *v)
{
  printf("-var-*\n");
  int i = 0;
  while (v)
  {
    printf("name%d:%s\n", i, v->name);
    printf("content%d:%s\n", i, v->content);
    printf("-|\n");
    v = v->next;
    i++;
  }
  printf("-----*\n");
}