#include "minipaint.h"

int	control(float x, float xb, float y, float yb, float rayon)
{
	float xbb;
	float ybb;

	xbb = xb - 1;
	ybb = yb;
	if (sqrt(((x - xbb) * (x - xbb)) + ((y - ybb) * (y - ybb))) >= rayon)
		return (1);
	xbb = xb;
	ybb = yb - 1;
	if (sqrt(((x - xbb) * (x - xbb)) + ((y - ybb) * (y - ybb))) >= rayon)
		return (1);

	xbb = xb + 1;
	ybb = yb;
	if (sqrt(((x - xbb) * (x - xbb)) + ((y - ybb) * (y - ybb))) >= rayon)
		return (1);

	xbb = xb;
	ybb = yb + 1;
	if (sqrt(((x - xbb) * (x - xbb)) + ((y - ybb) * (y - ybb))) >= rayon)
		return (1);

	xbb = xb + 1;
	ybb = yb + 1;
	if (sqrt(((x - xbb) * (x - xbb)) + ((y - ybb) * (y - ybb))) >= rayon)
		return (1);

	xbb = xb - 1;
	ybb = yb - 1;
	if (sqrt(((x - xbb) * (x - xbb)) + ((y - ybb) * (y - ybb))) >= rayon)
		return (1);

	xbb = xb - 1;
	ybb = yb + 1;
	if (sqrt(((x - xbb) * (x - xbb)) + ((y - ybb) * (y - ybb))) >= rayon)
		return (1);

	xbb = xb + 1;
	ybb = yb - 1;
	if (sqrt(((x - xbb) * (x - xbb)) + ((y - ybb) * (y - ybb))) >= rayon)
		return (1);
	return (0);
}

void	algo(char **buf, float width, float height, char vp, float x, float y, float rayon, char c)
{
	float	xb;
	float	yb;
	float	res;

	yb = 0;
	while (yb < height)
	{
		xb = 0;	
		while (xb < width)
		{
			res = sqrt(((x - xb) * (x - xb)) + ((y - yb) * (y - yb)));
			if (res <= rayon && vp == 'C')
				buf[(int)yb][(int)xb] = c;
			else if (res <= rayon && vp == 'c' && control(x, xb, y, yb, rayon))
				buf[(int)yb][(int)xb] = c;
			xb++;
		}
		yb++;
	}
}

int	boucle(int i, char **buf, char *str, float width, float height)
{
	char	vp;
	float	x;
	float 	y;
	float 	rayon;
	char	c;
	
	while (str[i])
	{
		if (str[i] != 'c' && str[i] != 'C')
			return (ft_error("5 Error\n"));
		vp = str[i++];
		while (str[i] == ' ')
			i++;
		if (ft_isdigit(str[i]) || str[i] == '-')
			x = ft_atoi(str, &i);
		else
			return (ft_error("6 Error\n"));
		if (ft_isdigit(str[i]) || str[i] == '-')
			y = ft_atoi(str, &i);
		else
			return (ft_error("7 Error\n"));
		if (ft_isdigit(str[i]))
			rayon = ft_atoi(str, &i);
		else
			return (ft_error("8 Error\n"));
		if (ft_isdigit(str[i]))
			return (ft_error("9 Error\n"));
		else
			c = str[i++];
		while (str[i] == ' ' || str[i] == '\n')
			i++;
		algo(buf, width, height, vp, x - 1, y - 1, rayon, c);
	}	
	int	j = 0;
	while (j < height)
	{
		write(1, buf[j], ft_strlen(buf[j]));
		write(1, "\n", 1);
		j++;
	}

	return (0);
}

int	pars(char *str)
{
	char	**buf;
	float	width;
	float	height;
	char	back;
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (ft_isdigit(str[i]))
		width = ft_atoi(str, &i);
	else
		return (ft_error(" 1 Error\n"));
	if (ft_isdigit(str[i]))
		height = ft_atoi(str, &i);
	else
		return (ft_error("2 Error\n"));
	if (!(width > 0 && width <= 300) || !(height > 0 && height <= 300))
		return (ft_error("3 Error\n"));
	if (ft_isdigit(str[i]))
		return (ft_error("4 Error\n"));
	else
		back = str[i++];
	while (str[i] == ' ' || str[i] == '\n')
		i++;
	
	buf = calloc(height + 1, sizeof(char*));
	int j = 0;
	while (j < height)
	{
		buf[j] = calloc(width + 1, sizeof(char));
		buf[j] = memset(buf[j], back, width);
		j++;
	}

	return (boucle(i, buf, str, width, height));
	return (0);
}
