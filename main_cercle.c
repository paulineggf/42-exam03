#include <libc.h>
#include <math.h>

int		ft_strlen(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int		ft_error(char *str)
{
	ft_putstr(str);
	return (1);
}

float	ft_atoi(char *str, int *i)
{
	float	res;
	float	after_coma;
	float	sign;
	float	count;

	res = 0.0;
	after_coma = 0.0;
	sign = 1.0;
	count = 1.0;
	if (str[*i] == '-')
	{
		sign *= -1.0;
		(*i)++;
	}
	while (ft_isdigit(str[*i]))
	{
		res = res * 10.0 + (str[*i] - 48);
		(*i)++;
	}
	if (str[*i] == '.')
	{
		(*i)++;
		while (ft_isdigit(str[*i]))
		{
			after_coma = after_coma * 10.0 + (str[*i] - 48);
			(*i)++;
			count *= 10.0;
		}
	}
	after_coma /= count;
	res = res + after_coma;
	res = res * sign;
	while (str[*i] == ' ' || str[*i] == '\n')
		(*i)++;
	return (res);
}

char	*ft_strjoin(char *str, char *buf)
{
	int		i;
	int		j;
	char	*new;

	j = 0;
	i = 0;
	new = calloc(ft_strlen(str) + ft_strlen(buf) + 1, sizeof(char));
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	while (buf[j])
	{
		new[i] = buf[j];
		i++;
		j++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}

int		calcul(float rayon, float x, float xb, float y, float yb)
{
	int		ret;
	float	xbb;
	float 	ybb;
	ret = 0;
	
	xbb = xb - 1;
	ybb = yb;
	ret = sqrt(((x - xbb) * (x - xb)) + ((y - ybb) * (y - ybb)));
	if (ret >= rayon)
		return (1);
	xbb = xb + 1;
	ybb = yb;
	ret = sqrt(((x - xbb) * (x - xbb)) + ((y - ybb) * (y - ybb)));
	if (ret >= rayon)
		return (1);
	xbb = xb;
	ybb = yb - 1;
	ret = sqrt(((x - xbb) * (x - xbb)) + ((y - ybb) * (y - ybb)));
	if (ret >= rayon)
		return (1);
	xbb = xb;
	ybb = yb + 1;
	ret = sqrt(((x - xbb) * (x - xbb)) + ((y - ybb) * (y - ybb)));
	if (ret >= rayon)
		return (1);	
	xbb = xb + 1;
	ybb = yb + 1;
	ret = sqrt(((x - xbb) * (x - xbb)) + ((y - ybb) * (y - ybb)));
	if (ret >= rayon)
		return (1);
	xbb = xb - 1;
	ybb = yb - 1;
	ret = sqrt(((x - xbb) * (x - xbb)) + ((y - ybb) * (y - ybb)));
	if (ret >= rayon)
		return (1);		
	xbb = xb + 1;
	ybb = yb - 1;
	ret = sqrt(((x - xbb) * (x - xbb)) + ((y - ybb) * (y - ybb)));
	if (ret >= rayon)
		return (1);
	xbb = xb - 1;
	ybb = yb + 1;
	ret = sqrt(((x - xbb) * (x - xbb)) + ((y - ybb) * (y - ybb)));
	if (ret >= rayon)
		return (1);			
	return (0);
}

void	draw_circle(char **buf, float x, float y, float rayon, float width, float height, char vp, char c)
{
	float	xb;
	float	yb;
	float	res;

	yb = 0.0;
	res = 0.0;
	while (yb < height)
	{
		xb = 0;
		while (xb < width)
		{
			res = sqrt(((x - xb) * (x - xb)) + ((y - yb) * (y - yb)));
			if (res <= rayon && vp == 'C')
				buf[(int)yb][(int)xb] = c;
			if (vp == 'c' && res <= rayon && calcul(rayon, x, xb, y, yb))
			{
				printf("res : %f && x : %f && xb : %f && y : %f && yb : %f\n", res, x, xb, y, yb);
				buf[(int)yb][(int)xb] = c;
			}
			xb++;
		}
		yb++;
	}
}


int		pars(char *str)
{
	int		i = 0;
	float	width;
	float	height;
	char	back;
	char	vp;
	float	x;
	float	y;
	float	rayon;
	char	c;
	char	**buf;

	width = ft_atoi(str, &i);
	if (!(width > 0 && width <= 300))
		return (ft_error("Error\n"));
	
	if (ft_isdigit(str[i]))
		height = ft_atoi(str, &i);
	else
		return (ft_error("Error\n"));
	
	if (!(height > 0 && height <= 300))
		return (ft_error("Error\n"));
	
	if (ft_isdigit(str[i]))
		return (ft_error("Error\n"));
	else
		back = str[i++];
	while (str[i] == ' ' || str[i] == '\n')
		i++;
	printf("width : %f\n", width);
	printf("height : %f\n", height);
	printf("back : %c\n", back);

	buf = calloc(height + 1, sizeof(char*));
	int	j = 0;
	while (j < height)
	{
		buf[j] = calloc(width + 1, sizeof(char));
		buf[j] = memset(buf[j], back, width);
		buf[j][(int)width] = '\0';
		printf("%s\n", buf[j]);
		j++;
	}

	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (ft_error("1 Error\n"));
		else
			vp = str[i++];
		while (str[i] == ' ')
			i++;
		x = ft_atoi(str, &i);
		
		if (ft_isdigit(str[i]) || str[i] == '-')
			y = ft_atoi(str, &i);
		else
			return (ft_error("2 Error\n"));
		
		if (ft_isdigit(str[i]))
			rayon = ft_atoi(str, &i);
		else
			return (ft_error("3 Error\n"));

		if (ft_isdigit(str[i]))
			return (ft_error("4 Error\n"));
		else
			c = str[i++];
		while (str[i] == ' ' || str[i] == '\n')
			i++;
	
		printf("vp : %c\n", vp);
		printf("x : %f\n", x);
		printf("y : %f\n", y);
		printf("rayon : %f\n", rayon);
		printf("c : %c\n", c);

		draw_circle(buf, x - 1, y - 1, rayon, width, height, vp, c);
	}
	j = 0;
	while (j < height)
	{
		printf("%s\n", buf[j]);
		j++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	FILE	*fd;
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
