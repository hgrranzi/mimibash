#include "mimibash.h"
int skipper(char *str)
{
	int i;

	i = 0;
	if (str)
	{
		while(str[i] == ' ')
			i++;
	}
	return(i);
}
int valid_input2(char *str, int i)
{

}
int valid_input(char *str)
{
	int i;
	int m;
	int n;

	i = skipper(str);
	n = ft_strlen(str);
	if (str[i]&& str[i + 1] && str[i] == '|' && str[i + 1] != '|')
	{
		write(1, "syntax error near unexpected token `|'\n", 39);
		return(0);
	}
	if (str[i] && str[i + 1] && str[i] == '|' && str[i + 1] == '|')
	{
		write(1, "syntax error near unexpected token `||'\n", 40);
		return(0);
	}
	if (str[i] && str[i + 1] && str[i] == '>' && str[i + 1] != '\0')
	{
		write(1, "syntax error near unexpected token `newline'\n", 40);
		return(0);
	}
	if (str[i] && str[i + 1] && str[i + 2] && str[i] == '>' && str[i + 1] != '>' str[i + 2] == '\0')
	{
		write(1, "syntax error near unexpected token `newline'\n", 40);
		return(0);
	}
	m = valid_input2(str, i);
	return (m);
}