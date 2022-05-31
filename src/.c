int	ft_scan_for_quotes(char **str)
{
	int	i;

	i = 0;
	while (**str != 0)
	{
		if (**str == '"')
		{
			i++;
			(*str)++;
			while (**str != '"')
				(*str)++;
			if (*str == '"')
				i++;
			if (*str == 0)
				return (i);
		}
		if (**str == 32 || **str == 0)
    	{
      		(*str)++;
			break;
   		}
		(*str)++;
	}
	return (i);
}
