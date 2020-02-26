#include "minipaint.h"

int	boucle(char **buf, char *str, int i, float width, float height)
{
	char	r;
	char	c;
	float	x;
	float	y;
	float	largeur;
	float	hauteur;

	while (str[i])
	{
		if (str[i] != 'r' && str[i] != 'R')
			return (ft_error("R\n"));
		else
			r = str[i++];
		while (str[i] == ' ')
			i += 1;
		if (ft_isdigit(str[i]) || str[i] == '-')
			x = ft_atoi(str, &i);
		else
			return (ft_error("x\n"));
		if (ft_isdigit(str[i]) || str[i] == '-')
			y = ft_atoi(str, &i);
		else
			return (ft_error("y\n"));
		if (ft_isdigit(str[i]) || str[i] == '-')
			largeur = ft_atoi(str, &i);
		else
			return (ft_error("largeur\n"));
		if (ft_isdigit(str[i]) || str[i] == '-')
			hauteur = ft_atoi(str, &i);
		else
			return (ft_error("hauteur\n"));
		if (ft_isdigit(str[i]))
			return (ft_error("c\n"));
		else
			c = str[i++];
		while (str[i] == ' ' || str[i] == '\n')
			i += 1;
		printf("r : %c\n", r);
		printf("width : %f\n", width);
		printf("height : %f\n", height);
		printf("x : %f\n", x);
		printf("y : %f\n", y);
		printf("largeur : %f\n", largeur);
		printf("hauteur : %f\n", hauteur);
		printf("c : %c\n", c);


		algo(buf, r, width, height, x - 1, y - 1, largeur - 1, hauteur - 1, c);
	}
	int	j = 0;
	while (j < height)
	{
		ft_putstr(buf[j]);
		write(1, "\n", 1);
		j++;
	}
	return (0);
}

int	pars(char *str)
{
	float	width;
	float	height;
	char	back;
	int	i;
	char	**buf;

	i = 0;
	while (str[i] == ' ')
		i += 1;
	if (ft_isdigit(str[i]))
		width = ft_atoi(str, &i);
	else
		return (ft_error("width\n"));
	if (ft_isdigit(str[i]))
		height = ft_atoi(str, &i);
	else
		return (ft_error("height\n"));
	if (ft_isdigit(str[i]))
		return (ft_error("back\n"));
	else
		back = str[i++];
	while (str[i] == ' ' || str[i] == '\n')
		i += 1;
	buf = calloc(height + 1, sizeof(char*));
	int	j = 0;
	while (j < height)
	{
		buf[j] = calloc(width + 1, sizeof(char));
		buf[j] = memset(buf[j], back, width);
		j++;
	}
	return (boucle(buf, str, i, width, height));
	return (0);
}
