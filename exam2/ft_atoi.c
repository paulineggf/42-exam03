#include "minipaint.h"

float	ft_atoi(char *str, int *i)
{
	float	res;
	float	reste;
	float	sign;
	float	div;

	div = 1;
	res = 0;
	reste = 0;
	sign = 1;
	if (str[*i] == '-')
	{
		sign *= -1;
		*i += 1;
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
