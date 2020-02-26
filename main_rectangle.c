#include <libc.h>

int		ft_strlen(char *str)
{
	int 	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*s3;

	i = 0;
	j = 0;
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}

int		ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int		ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

float	ft_atoi(char *str, int *i)
{
	float	res;
	float	reste;
	float	sign;
	float	div;

	div = 1;
	sign = 1;
	res = 0;
	reste = 0;
	if (str[*i] == '-')
	{
		sign *= -1;
		(*i)++;
	}
	while (ft_isdigit(str[*i]))
	{
		res = res * 10 + str[*i] - 48;
		(*i)++;
	}

	if (str[*i] == '.')
	{
		(*i)++;
		while (ft_isdigit(str[*i]))
		{
			reste = reste * 10 + str[*i] - 48;
			(*i)++;
			div *= 10;
		}
		reste /= div;

	}
	res += reste;
	while (str[*i] == ' ' || str[*i] == '\n')
		(*i)++;
	return (res * sign);
}

void	draw_rectangle(int width, int height, char r, int x, int y, float largeur, float hauteur, char c, char **buf)
{
	int		xb;
	int		yb;

	yb = y;
	printf("xb : %d && x : %d && yb : %d && y : %d\n", xb, x , yb, y);
	while (yb - y < hauteur && yb < height)
	{
		xb = x;
		while (xb - x < largeur && xb < width)
		{
			if (xb >= 0 && yb >= 0)
			{
				if (yb >= y && xb >= x)
				{
					if (x == xb || y == yb)
						buf[yb][xb] = c;
					else if (x + largeur - 1 == xb || y + hauteur - 1 == yb)
						buf[yb][xb] = c;
					else if (r == 'R' && xb > x && yb > y)
						buf[yb][xb] = c;
				}
			}
			xb++;
		}
		yb++;
	}
}


int		pars(char *str)
{
	int		i;
	float	width;
	float	height;
	char	back;
	char	r;
	float	x;
	float	y;
	float	largeur;
	float	hauteur;
	char	c;
	char	**buf;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (ft_isdigit(str[i]))
		width = ft_atoi(str, &i);
	else
		return (ft_error("0 Error\n"));	
	if (ft_isdigit(str[i]))
		height = ft_atoi(str, &i);
	else
		return (ft_error("-1 Error\n"));
	if (!(width > 0 && width <= 300) || !(height > 0 && height <= 300))
		return (ft_error("1 Error\n"));
	if (ft_isdigit(str[i]))
		return (ft_error("2 Error\n"));
	back = str[i++];
	while (str[i] == '\n' || str[i] == ' ')
		i++;
	
	printf("back : %c && width : %f && height : %f\n", back, width, height);

	buf = calloc(height + 1, sizeof(char*));
	int	j = 0;
	while (j < height)
	{
		buf[j] = calloc(width + 1, sizeof(char));
		buf[j] = memset(buf[j], back, width);
		j++;
	}

	while (str[i])
	{
		if (str[i] != 'r' && str[i] != 'R')
			return (ft_error("3 Error\n"));
		r = str[i++];
		while (str[i] == ' ')
			i++;
		if (ft_isdigit(str[i]) || str[i] == '-')
			x = ft_atoi(str, &i);
		else
			return (ft_error("4 Error\n"));
		if (ft_isdigit(str[i]) || str[i] == '-')
			y = ft_atoi(str, &i);
		else
			return (ft_error("5 Error\n"));
		if (ft_isdigit(str[i]) || str[i] == '-')
			largeur = ft_atoi(str, &i);
		else
			return (ft_error("6 Error\n"));
		if (ft_isdigit(str[i]) || str[i] == '-')
			hauteur = ft_atoi(str, &i);
		else
			return (ft_error("7 Error\n"));	
		if (ft_isdigit(str[i]))
			return (ft_error("8 Error\n"));
		else
			c = str[i++];
		while (str[i] == ' ' || str[i] == '\n')
			i++;

		printf("r : %c && x : %f && y : %f && largeur : %f && hauteur : %f && c : %c\n", r, x, y, largeur, hauteur, c);
		
		draw_rectangle(width, height, r, x - 1, y - 1, largeur, hauteur, c, buf);
	}

	j = 0;
	while (j < height)
	{
		write(1, buf[j], ft_strlen(buf[j]));
		write(1, "\n", 1);
		j++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	FILE 	*fd;
	int		ret;
	char	buf[33];
	char	*str;

	if (argc == 2)
	{
		str = calloc(1, sizeof(char));
		fd = fopen(argv[1], "r");
		if (fd == NULL)
			return (ft_error("Error\n"));
		while ((ret = fread(buf, 1, 32, fd)) > 0)
		{
			buf[ret] = '\0';
			str = ft_strjoin(str, buf);
		}
		if (ret != 0)
			return (ft_error("Error\n"));
		return (pars(str));
	}
	else
		return (ft_error("Error\n"));
	return (0);	
}