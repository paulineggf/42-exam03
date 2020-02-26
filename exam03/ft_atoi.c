#include "minipaint.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

float	ft_atoi(char *str, int *i)
{	
	float	res;
	float	reste;
	float	div;
	float	sign;

	sign = 1;
	res = 0;
	reste = 0;
	div = 1;
	if (str[*i] == '-')
	{
		*i += 1;
		sign *= -1;
	}
	while (ft_isdigit(str[*i]))
	{
		res = res * 10 + str[*i] - 48;
		*i += 1;
	}
	if (str[*i] == '.')
	{
		*i += 1;
		while (ft_isdigit(str[*i]))
		{
			reste = reste * 10 + str[*i] - 48;
			*i += 1;
			div *= 10;
		}
		reste /= div;
	}
	res += reste;
	while (str[*i] == ' ' || str[*i] == '\n')
		*i += 1;
	return (res * sign);
}
